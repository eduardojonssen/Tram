#TRAM
Tram is a personal project where I try to implement Vulkan as the main renderer API. This project is intended for personal studies only.

##Pre-requisites
This project is configured to build x64 applications only. No need to configure x86 (32 bits) settings or packages.

###Vulkan SDK
Download and install the latest [Vulkan SDK](https://vulkan.lunarg.com/sdk/home) if you don't have it yet.

###GLFW
For window management, [GLFW](https://www.glfw.org/download.html) is required.

##Configuring Visual Studio
Open the solution, right click **Tram.Engine** project and choose **Properties**.

###Include directories
Make sure you have the following entries under *C/C++ > General > Additional Include Directories*:

```
E:\GLFW\glfw-3.3.3.bin.WIN64\include;$(VULKAN_SDK)\Include;
```

Replace the **E:\GLFW\glfw-3.3.3.bin.WIN64** with the path to your GLFW install/download folder.

###Library directories
Under *Linker > General > Additional Library Directories*, check if the GLFW and Vulkan lib dirs are defined:

```
E:\GLFW\glfw-3.3.3.bin.WIN64\lib-vc2019;$(VULKAN_SDK)\Lib;
```

Again, replace the **E:\GLFW\glfw-3.3.3.bin.WIN64** with the path to your GLFW install/download folder.

###Aditional Dependencies
Lastly, under *Linker > Input*, check if the following entries are present:

```
vulkan-1.lib;glfw3.lib;
```