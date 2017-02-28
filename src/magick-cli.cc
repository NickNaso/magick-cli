/*******************************************************************************
 * Copyright (c) 2017 Nicola Del Gobbo
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the license at http://www.apache.org/licenses/LICENSE-2.0
 *
 * THIS CODE IS PROVIDED ON AN *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS
 * OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY
 * IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
 * MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 * See the Apache Version 2.0 License for specific language governing
 * permissions and limitations under the License.
 *
 * Contributors - initial API implementation:
 * Nicola Del Gobbo <nicoladelgobbo@gmail.com>
 ******************************************************************************/

#include "magick-cli.h"

class ImageMagickWorker : public AsyncWorker {
    public:
        ImageMagickWorker(Callback *callback, string RAWcmd) 
            : AsyncWorker(callback), RAWcmd(RAWcmd), res(0) {}
        ~ImageMagickWorker() {} 

        void Execute() {
            res = 0;
            vector<string> explodedCmd;
            istringstream iss(RAWcmd);
            for (string RAWcmd; iss >> RAWcmd;)
                explodedCmd.push_back(RAWcmd); 
            int imargc = static_cast<int>(explodedCmd.size());
            char ** imargv = new char*[imargc];
            for(int i = 0; i < imargc; i++) {
                imargv[i] = (char*)explodedCmd[i].c_str();
            }
            MagickCoreGenesis("MagickCLI", MagickFalse);
            {
                ImageInfo *image_info = AcquireImageInfo();
                ExceptionInfo *exception = AcquireExceptionInfo();
                (void)MagickImageCommand(image_info, imargc, imargv, NULL, exception);
                if (exception->severity != UndefinedException) {
                    msg <<  "Sorry error happened executing ImageMagick command. Error: " << exception->reason << ". " << exception->description;
                    res = 1;
                } else {
                    res = 0;
                }
                delete[] imargv;
                image_info = DestroyImageInfo(image_info);
                exception = DestroyExceptionInfo(exception);
            }
            MagickCoreTerminus();
        }

        void HandleOKCallback() {
            Nan::HandleScope();
            Local<Value> argv[1];
            if (res == 0) {
                argv[0] = Null();
            } else {
                argv[0] = Error(Nan::New<String>(msg.str()).ToLocalChecked());
            }
            callback->Call(1, argv);
        } 

        private:
            string RAWcmd;
            int res;
            stringstream msg;
};

NAN_METHOD(Version)
{
    Nan::HandleScope();
    info.GetReturnValue().Set(Nan::New<String>(MagickLibVersionText).ToLocalChecked());
}

NAN_METHOD(Execute)
{
    Callback *callback = new Callback(info[1].As<Function>());
    Local<String> JScmd = Local<String>::Cast(info[0]);
    string RAWcmd = *String::Utf8Value(JScmd);
    AsyncQueueWorker(new ImageMagickWorker(callback, RAWcmd));
}

NAN_METHOD(ExecuteSync)
{
    Nan::HandleScope();
    if (info.Length() < 1)
    {
        return Nan::ThrowError("Sorry executeSync() method requires 1 argument that represent the ImageMagick command.");
    }
    if (!info[0]->IsString())
    {
        return Nan::ThrowError("Sorry executeSync() method's argument should be a string.");
    }
    Local<String> IMcmd = Local<String>::Cast(info[0]);
    string RAWcmd = *String::Utf8Value(IMcmd);
    vector<string> explodedCmd;
    istringstream iss(RAWcmd);
    for (string RAWcmd; iss >> RAWcmd;)
        explodedCmd.push_back(RAWcmd); 
    int imargc = static_cast<int>(explodedCmd.size());
    char ** imargv = new char*[imargc];
    for(int i = 0; i < imargc; i++) {
        imargv[i] = (char*)explodedCmd[i].c_str();
    }
    MagickCoreGenesis("MagickCLI", MagickFalse);
    {
        ImageInfo *image_info = AcquireImageInfo();
        ExceptionInfo *exception = AcquireExceptionInfo();
        (void)MagickImageCommand(image_info, imargc, imargv, NULL, exception);
        if (exception->severity != UndefinedException)
        {
            delete[] imargv;
            stringstream msg; 
            msg << "Sorry error happened executing ImageMagick command. Error: " << exception->reason << ". " << exception->description;
            image_info = DestroyImageInfo(image_info);
            exception = DestroyExceptionInfo(exception);
            MagickCoreTerminus();
            return Nan::ThrowError(Nan::New<String>(msg.str()).ToLocalChecked()); 
        } 
        delete[] imargv;
        image_info = DestroyImageInfo(image_info);
        exception = DestroyExceptionInfo(exception);
    }
    MagickCoreTerminus();
    return;  
}

//////////////////////////// INIT & CONFIG MODULE //////////////////////////////

void Init(Local<Object> exports)
{
    exports->Set(Nan::New("version").ToLocalChecked(),
                 Nan::New<FunctionTemplate>(Version)->GetFunction());

    exports->Set(Nan::New("execute").ToLocalChecked(),
                 Nan::New<FunctionTemplate>(Execute)->GetFunction());

    exports->Set(Nan::New("executeSync").ToLocalChecked(),
                 Nan::New<FunctionTemplate>(ExecuteSync)->GetFunction());
}

NODE_MODULE(MagickCLI, Init)

////////////////////////////////////////////////////////////////////////////////
