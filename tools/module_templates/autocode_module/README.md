# Auto-code Module Template
If you intend to create any `autocode_module` inside `application`, use this folder as a template to create new module.

## Module Structure
Module will follow same structure as that of IDC5:
1. Layer
2. Submodule
3. Model

Layer is nothing but the `autocode_module`.

# Autocode Module Folder Structure
```
autocode_module
└── sub_module
    └── sub_module_model
        ├── model
        │   ├── frame
        │   │   └── MODEL.slx
        │   ├── modules
        │   │   └── MODEL_SUB_NAME_SHELL.slx
        ├── para
        │   ├── MODEL_init.m
        ├── testsetup
        │   ├── tpttesting
        │   │   ├── MODEL_SUB_NAME_SHELL
        │   │   │   ├── MODEL_SUB_NAME_SHELL.tpt
        │   │   │   ├── MODEL_SUB_NAME_SHELL_TPT_testframe.slx
        │   │   │   └── MODEL_SUB_NAME_SHELL_TPT_tpt_io.m
        ├── toolchain
        │   ├── datadictionary
        │   │   └── MODEL.dd
        │   └── MODEL_prj_info.m
        ├── .a2l file
        └── auto-generated C++ files
```
_Please follow the aforementioned folder strucutre._
