/*******************************************************************************
 * Copyright (c) 2018 Nicola Del Gobbo
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
 * Mauro Doganieri <mauro.doganieri@gmail.com>
 ******************************************************************************/

#include "magick-cli.h"

// Lifeclycle management for the MagickCLI instance
class MagickCLIManager
{
  private:
    static bool exists;
    mutex mc;
    static MagickCLIManager *instance;
    MagickCLIManager() 
    {
        // NOOP
    }

  public:
    static MagickCLIManager *GetInstance();
    ~MagickCLIManager() 
    {
        exists = false;
    };
    void Execute(int gsargc, char *gsargv[]);
};

bool MagickCLIManager::exists = false;
MagickCLIManager *MagickCLIManager::instance = NULL;
// Static method that create or simple return the instance of the MagickCLItManager
// following the singleton design pattern
MagickCLIManager *MagickCLIManager::GetInstance()
{
    if (!exists)
    {
        instance = new MagickCLIManager();
        exists = true;
        return instance;
    }
    else
    {
        return instance;
    }
}

void MagickCLIManager::Execute(int imargc, char *imargv[])
{
    lock_guard<mutex> lk(mc);
    MagickCoreGenesis("MagickCLI", MagickFalse);
    {
        ImageInfo *image_info = AcquireImageInfo();
        ExceptionInfo *exception = AcquireExceptionInfo();
        (void)MagickImageCommand(image_info, imargc, imargv, NULL, exception);
        if (exception->severity != UndefinedException) 
        {
            throw "Sorry error happened executing ImageMagick command. Error: " + string(exception->reason) + ". " + string(exception->description);
        }
        image_info = DestroyImageInfo(image_info);
        exception = DestroyExceptionInfo(exception);
    }
    MagickCoreTerminus();  
}

class ImageMagickWorker : public Napi::AsyncWorker 
{
    public:
        ImageMagickWorker(Napi::Function& callback, string RAWcmd) 
            : Napi::AsyncWorker(callback), RAWcmd(RAWcmd) {}
        ~ImageMagickWorker() {} 

        void Execute() {
            vector<string> explodedCmd;
            istringstream iss(RAWcmd);
            for (string RAWcmd; iss >> RAWcmd;)
                explodedCmd.push_back(RAWcmd); 
            int imargc = static_cast<int>(explodedCmd.size());
            char ** imargv = new char*[imargc];
            for(int i = 0; i < imargc; i++) {
                imargv[i] = (char*)explodedCmd[i].c_str();
            }
            try 
            { 
                MagickCLIManager *mc = MagickCLIManager::GetInstance();
                mc->Execute(imargc, imargv);
                delete[] imargv;
            }
            catch (exception &e)
            {
                delete[] imargv;
                SetError(Napi::String::New(Env(), e.what()));
            }
        }

        void OnOK() 
        {
            Napi::HandleScope scope(Env());
            Callback().Call({Env().Null()});
        } 

        private:
            string RAWcmd;
};

Napi::Value Version(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    return Napi::String::New(env, MagickLibVersionText);
}

void Execute(const Napi::CallbackInfo& info)
{
    Napi::Function callback = info[1].As<Napi::Function>();
    string RAWcmd = info[0].As<Napi::String>().Utf8Value();
    ImageMagickWorker* im = new ImageMagickWorker(callback, RAWcmd);
    im->Queue();
}

void ExecuteSync(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1)
    {
        throw Napi::Error::New(env, "Sorry executeSync() method requires 1 argument that represent the ImageMagick command.");
    }
    if (!info[0].IsString())
    {
        throw Napi::Error::New(env, "Sorry executeSync() method's argument should be a string.");
    }
    string RAWcmd = info[0].As<Napi::String>().Utf8Value();
    vector<string> explodedCmd;
    istringstream iss(RAWcmd);
    for (string RAWcmd; iss >> RAWcmd;)
        explodedCmd.push_back(RAWcmd); 
    int imargc = static_cast<int>(explodedCmd.size());
    char ** imargv = new char*[imargc];
    for(int i = 0; i < imargc; i++) 
    {
        imargv[i] = (char*)explodedCmd[i].c_str();
    }
    try
    {
        MagickCLIManager *mc = MagickCLIManager::GetInstance();
        mc->Execute(imargc, imargv);
        delete[] imargv;
    }
    catch (exception &e)
    {
        delete[] imargv;
        throw Napi::Error::New(env, e.what());
    }
    return;  
}

//////////////////////////// INIT & CONFIG MODULE //////////////////////////////

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "version"),
        Napi::Function::New(env, Version));
    exports.Set(Napi::String::New(env, "execute"),
        Napi::Function::New(env, Execute));
    exports.Set(Napi::String::New(env, "executeSync"), 
        Napi::Function::New(env, ExecuteSync));
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)

////////////////////////////////////////////////////////////////////////////////
