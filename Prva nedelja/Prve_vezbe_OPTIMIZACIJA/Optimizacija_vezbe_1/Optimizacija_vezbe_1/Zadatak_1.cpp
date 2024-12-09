{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "cargo build",
            "type": "shell",
            "command": "cargo",
            "args": [
                "build",
                "--target",
                "thumbv7em-none-eabihf"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": [
                "$rustc"
            ]
        },
        {
            "label": "generate .bin from ELF",
            "type": "shell",
            "command": "arm-none-eabi-objcopy.exe",
            "args": [
                "-O",
                "binary",
                "template",
                "output.bin"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": ["$rustc"],
            "presentation": {
                "echo": true,
                "reveal": "silent",
                "focus": false,
                "panel": "shared",
                "showReuseMessage": true,
                "clear": false
            }
        }
    ]
}
