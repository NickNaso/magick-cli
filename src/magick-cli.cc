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

/*class MagickCLIWorker : public AsyncWorker
{
  public:
    MagickCLIWorker(Callback *callback, string RAWcmd)
        : AsyncWorker(callback), RAWcmd(RAWcmd), res(0) {}
    ~MagickCLIWorker() {}

    void Execute()
    {
        /*res = 0;
            vector<string> explodedCmd;
            istringstream iss(RAWcmd);
            for(string RAWcmd; iss >> RAWcmd;)
                explodedCmd.push_back(RAWcmd);
            void *minst;
            int code, exit_code;
            int gsargc = static_cast<int>(explodedCmd.size());
            char ** gsargv = new char*[gsargc];
            for(int i = 0; i < gsargc; i++) {
                gsargv[i] = (char*)explodedCmd[i].c_str();
            }
            code = gsapi_new_instance(&minst, NULL);
            if (code < 0) {
                msg << "Sorry error happened creating Ghostscript instance. Error code: " << code;
                res = 1;
            } else {
                gsapi_set_stdio(minst, gsdll_stdin, gsdll_stdout, gsdll_stderr);
                code = gsapi_set_arg_encoding(minst, GS_ARG_ENCODING_UTF8);
                if (code == 0)
                    code = gsapi_init_with_args(minst, gsargc, gsargv); 
                exit_code = gsapi_exit(minst);
                if ((code == 0) || (code == gs_error_Quit))
                    code = exit_code;
                gsapi_delete_instance(minst);
                if ((code == 0) || (code == gs_error_Quit)) {
                    res = 0;
                } else {
                    msg << "Sorry error happened executing Ghostscript command. Error code: " << code;
                    res = 1;
                }        
            }
            delete[] gsargv;*/
    }

    void HandleOKCallback()
    {
        Nan::HandleScope();
        /*Local<Value> argv[1];
            if (res == 0) {
                argv[0] = Null();
            } else {
                argv[0] = Error(Nan::New<String>(msg.str()).ToLocalChecked());
            }
            callback->Call(1, argv);*/
    }

  private:
    string RAWcmd;
    int res;
    stringstream msg;
};*/

NAN_METHOD(Version)
{
    Nan::HandleScope();
    info.GetReturnValue().Set(Nan::New<String>(MagickLibVersionText).ToLocalChecked());
}

/*NAN_METHOD(Execute)
{
    //Callback *callback = new Callback(info[1].As<Function>());
    //Local<String> JScmd = Local<String>::Cast(info[0]);
    //string RAWcmd = *String::Utf8Value(JScmd);
    //AsyncQueueWorker(new GhostscriptWorker(callback, RAWcmd));
}*/

/*NAN_METHOD(ExecuteSync)
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

    MagickCoreGenesis("js.png", MagickFalse);

    {
        MagickBooleanType status;

        ImageInfo *image_info = AcquireImageInfo();
        ExceptionInfo *exception = AcquireExceptionInfo();

        int arg_count;
        char *args[] = {"magick", "-size", "100x100", "xc:red",
                        "(", "rose:", "-rotate", "-90", ")",
                        "+append", "show:", NULL};

        for (arg_count = 0; args[arg_count] != (char *)NULL; arg_count++)
            ;

        (void)MagickImageCommand(image_info, arg_count, args, NULL, exception);

        if (exception->severity != UndefinedException)
        {
            CatchException(exception);
            //fprintf(stderr, "Major Error Detected\n");
        }

        image_info = DestroyImageInfo(image_info);
        exception = DestroyExceptionInfo(exception);
    }
    MagickCoreTerminus();

    /*void *minst;
    int code, exit_code;
    int gsargc = static_cast<int>(explodedCmd.size());    
    char ** gsargv = new char*[gsargc];
    for(int i = 0; i < gsargc; i++) {
        gsargv[i] = (char*)explodedCmd[i].c_str();
    }
    code = gsapi_new_instance(&minst, NULL);
    if (code < 0) {
        delete[] gsargv;
        stringstream msg; 
        msg << "Sorry error happened creating Ghostscript instance. Error code: " << code;
        return Nan::ThrowError(Nan::New<String>(msg.str()).ToLocalChecked());
    }    
    gsapi_set_stdio(minst, gsdll_stdin, gsdll_stdout, gsdll_stderr);
    code = gsapi_set_arg_encoding(minst, GS_ARG_ENCODING_UTF8);
    if (code == 0)
        code = gsapi_init_with_args(minst, gsargc, gsargv);
    exit_code = gsapi_exit(minst);
    if ((code == 0) || (code == gs_error_Quit))
	code = exit_code;
    gsapi_delete_instance(minst);
    if ((code == 0) || (code == gs_error_Quit)) {
        delete[] gsargv;
        return;
    } else {
        delete[] gsargv;
        stringstream msg; 
        msg << "Sorry error happened executing Ghostscript command. Error code: " << code;
        return Nan::ThrowError(Nan::New<String>(msg.str()).ToLocalChecked());
    } */
//}

//////////////////////////// INIT & CONFIG MODULE //////////////////////////////

void Init(Local<Object> exports)
{
    exports->Set(Nan::New("version").ToLocalChecked(),
                 Nan::New<FunctionTemplate>(Version)->GetFunction());

    /*exports->Set(Nan::New("execute").ToLocalChecked(),
                 Nan::New<FunctionTemplate>(Execute)->GetFunction());*/

    /*exports->Set(Nan::New("executeSync").ToLocalChecked(),
                 Nan::New<FunctionTemplate>(ExecuteSync)->GetFunction());*/
}

NODE_MODULE(MagickCLI, Init)

////////////////////////////////////////////////////////////////////////////////
