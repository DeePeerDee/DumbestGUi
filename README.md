# Dumbest GUI
---
### Overview

##### This is a GUI for nothing.
---
**System and Tool Requirements**

- **Target Operating System:** Windows 64-bit
- **Compiler:** GNU G++
- **Extra Tools** windres *(included in gcc if installed through pacman)*
---
### Building the resource file

Provided with a simple resource.rc file. (Configure to your liking)

```bash
windres -i resource.rc -o <output-file-name>.o
```
### Compilation and Linking

Build the executable GUI window
```
g++ <windres-output>.o test.cpp -o <executable-name>.exe
```

---

**Todos:**
- [x] Create a simple window. Even if the dumbest you can create.
- [x] Learn how to handle event dispatches. (Button Click for Example).
- [x] Create a custom resource (like Custom Icon) and use as Window and Taskbar Icon.
- [x] Create Toolbar and Menu
- [ ] Enhance if possible
---