/*
    MIT License

    Copyright (c) 2024 Caio Couto

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <tchar.h>

#define MAX_BUDDIES 3

int WINAPI get_process_counter(TCHAR* sFileName){
    int process_counter = 0;    

    PROCESSENTRY32 entry = {0}; 
    entry.dwSize = sizeof(PROCESSENTRY32);
    
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    
    if(Process32First(hSnap, &entry)){
        while(Process32Next(hSnap, &entry)){
            if(!stricmp(entry.szExeFile, sFileName)){
                process_counter++;
            }
        }
    }

    return process_counter;
}

DWORD WINAPI spawn_message_box(LPVOID lpArg) {
    do {
        MessageBoxW(
            NULL,
            (LPCWSTR)L"Somestring",
            NULL,
            MB_OK | MB_ICONHAND
        );
    } while (TRUE);
}

TCHAR* WINAPI get_filename(TCHAR* filepath) {
    size_t path_string_size = strlen(filepath) - 1ULL;

    for (int i = path_string_size; i >= 0; i--){
        if (filepath[i] == '\\') {
            filepath = filepath + (i + 1); 
            return filepath;
        }
    }

    return filepath;
}

int main(int argc, TCHAR* argv[]) {
    DWORD thread_id;    

    HANDLE message_box_thread = CreateThread(
        NULL,
        0,
        &spawn_message_box,
        NULL,
        0,
        &thread_id
    );

    int process_counter = 0;    
    TCHAR* filename = get_filename(argv[0]);

    do {
        process_counter = get_process_counter(filename);
        printf("%d\n", process_counter);

        if (process_counter < MAX_BUDDIES) {
            STARTUPINFOA* startup_info = malloc(sizeof(STARTUPINFOW));
            PROCESS_INFORMATION* process_info = malloc(sizeof(PROCESS_INFORMATION));

            CreateProcessA(
                argv[0],
                NULL,
                NULL,
                NULL,
                FALSE,
                0,
                NULL,
                NULL,
                startup_info,
                process_info
            );
            WaitForSingleObject(process_info->hProcess, INFINITE);
        }

    } while (TRUE);

    return EXIT_SUCCESS;
}
