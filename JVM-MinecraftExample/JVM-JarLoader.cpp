/*
 * Copyright 2021 AFYaan
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License atv
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define _CRT_SECURE_NO_WARNINGS

#include "Loader.h"
#include "LoaderUtils.h"
#include "Resources.h"
#include "Utils.h"

string ExeDir() {
    char result[MAX_PATH];
    string dir = string(result, GetModuleFileNameA(NULL, result, MAX_PATH));
    size_t last = dir.find_last_of("\\");

    return dir.substr(0, last);
}

int main(int argsLength, const char* args[])
{
    string dir = ExeDir();
    string gameDir = dir + string("\\gameDir");
    string assetsDir = gameDir + string("\\assets");
    string jarPath = gameDir + string("\\versions\\1.8.8\\1.8.8-resources.jar");
    string binariesDir = gameDir + string("\\bin\\binaries");
    string libraries = getLibraries(gameDir);

    string optClientJar = string("-Dminecraft.client.jar=") + jarPath;
    string optLibraryPath = string("-Djava.library.path=") + binariesDir;
    string optClassPath(string("-Djava.class.path=") + libraries);

    const char* filename = jarPath.c_str();
    FILE* inFile = fopen(filename, "rb");

    if (inFile == NULL) {
        return 0;
    }


    //Resources file
    string resPath = GetExeDir() + string("\\JVM_TEST-resources.jar");

    string mainMethod("net/minecraft/client/main/Main");
    unique_ptr<Loader> loader(new Loader(jarPath, mainMethod));
    loader->AddJVMArg(optLibraryPath.c_str());
    loader->AddJVMArg(optClientJar.c_str());
    loader->AddJVMArg(optClassPath.c_str());
    loader->AddArg("--username");
    loader->AddArg("AFYaan");
    loader->AddArg("--version");
    loader->AddArg("1.8.8");
    loader->AddArg("--gameDir");
    loader->AddArg(gameDir.c_str());
    loader->AddArg("--assetsDir");
    loader->AddArg(assetsDir.c_str());
    loader->AddArg("--assetIndex");
    loader->AddArg("1.8");
    loader->AddArg("--uuid");
    loader->AddArg("7dc90011f7e74489a10975df0c949993");
    loader->AddArg("--accessToken");
    loader->AddArg("0");

    loader->AddArg("--userProperties");
    loader->AddArg("{}");
    loader->AddArg("--userType");
    loader->AddArg("");

    loader->SetPassword("testpassword");
    loader->RunFromMemory(rawData, sizeof(rawData), args, argsLength);
}