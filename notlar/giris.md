# C/GCC + GDB ile VS Code Kurulum ve Debug Akışı

## 1. Ortam Kurulumu

**MSYS2 + MinGW-w64**  

1. <https://www.msys2.org> adresinden `msys2-x86_64-*.exe` indirilir ve `C:\msys64` altında kurulur.  
2. MSYS2 MSYS terminali açılır ve aşağıdaki komutlar çalıştırılır:  

   ```bash
   pacman -Syu       # ilk güncelleme
   pacman -Su        # ikinci güncelleme
   pacman -S --needed mingw-w64-x86_64-toolchain
   ```  

3. `C:\msys64\mingw64\bin` dizini **Sistem → Ortam Değişkenleri → Path** içine eklenir.  
4. VS Code’u yeniden başlatıp aşağıyı çalıştırarak doğrulayın:  

   ```bash
   gcc --version
   ```

## 2. VS Code & Uzantılar

- VS Code indir: <https://code.visualstudio.com>  
- Yükleyin:  
  - **C/C++** (ms-vscode.cpptools)  
  - **CMake Tools** (isteğe bağlı)  
  - **Code Runner** (isteğe bağlı)

## 3. `tasks.json` (Otomatik Derleme)

Proje klasörünüzde `.vscode/tasks.json` oluşturun:

```jsonc
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "build C",
      "type": "shell",
      "command": "gcc",
      "args": [
        "${file}",
        "-g",
        "-o",
        "${fileBasenameNoExtension}.exe"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      }
    }
  ]
}
```

- **Ctrl+Shift+B** ile derleme → `.exe` dosyası oluşur.

## 4. `launch.json` (Debug Yapılandırması)

Proje klasörünüzde `.vscode/launch.json` oluşturun veya açın:

```jsonc
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "(gdb) Launch",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/${fileBasenameNoExtension}.exe",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${fileDirname}",
      "environment": [],
      "externalConsole": false,
      "console": "internalConsole",
      "internalConsoleOptions": "neverOpen",
      "preLaunchTask": "build C",
      "MIMode": "gdb",
      "miDebuggerPath": "C:\msys64\mingw64\bin\gdb.exe",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        },
        {
          "description": "Intel syntax",
          "text": "-gdb-set disassembly-flavor intel",
          "ignoreFailures": true
        }
      ]
    }
  ]
}
```

## 5. Derleyici vs Debugger

- **`gcc`**: Kaynak (`.c`) dosyasını derleyerek yürütülebilir (`.exe`) dosya üretir.  
- **`gdb`**: Oluşan `.exe` dosyasını adım adım çalıştırmayı, breakpoint koymayı, değişkenleri izlemeyi sağlar.

## 6. Sık Karşılaşılan Hatalar & Çözümleri

| Hata Mesajı                                                 | Çözüm                                                                                          |
|-------------------------------------------------------------|------------------------------------------------------------------------------------------------|
| `bash: gcc: command not found`                              | PATH’i kontrol et, VS Code’u yeniden başlat                                                     |
| `program '.../a.exe' does not exist`                        | `program` yolunu `hello.exe` veya `${fileBasenameNoExtension}.exe` yap                          |
| `The value of miDebuggerPath is invalid`                    | `miDebuggerPath`’i doğru GDB yolu (örn. `C:\msys64\mingw64\bin\gdb.exe`) ile güncelle           |
| `link.exe only usable from Developer Command Prompt for VS` | MSVC yerine MinGW/GCC yapılandırması kullan veya VS Code’u Developer Command Prompt’tan başlat       |

## 7. İlk Programınızı Çalıştırma

1. `hello.c` dosyası oluşturun:

   ```c
   #include <stdio.h>
   int main(void) {
       printf("Merhaba, C dünyası!\n");
       return 0;
   }
   ```

2. **Ctrl+Shift+B** ile derleyin → `hello.exe` oluşur.  
3. **F5** ile debug başlatın; Debug Console’da çıktı görünür.
