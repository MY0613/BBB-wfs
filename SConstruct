
env = Environment()
env.Append(tools = ['mingw'])

# ccflags = ['-E', '-dDI']
# env.Append(CCFLAGS = ccflags)

# stdlib_inc = 'C:/mingw-w64/i686-6.3.0-posix-dwarf-rt_v5-rev1/mingw32/i686-w64-mingw32/include'
stdlib_inc = ''
libusb_inc = 'C:/Users/Brad/Documents/libusb-1.0.21/include/libusb-1.0'
app_inc = 'C:/Users/Brad/Documents/libusb-sample/inc'
env.Append(CPPPATH = [libusb_inc, app_inc])

# C:\Users\Brad\Documents\libusb-1.0.21\MinGW64\dll
libusb_pth = 'C:/Users/Brad/Documents/libusb-1.0.21/MinGW32/dll'
libusb_bin = 'libusb-1.0'
env.Append(LIBPATH = [libusb_pth])
env.Append(LIBSUFFIX = ['.dll', '.dll.a'])

# print env.Dump()
env.Program(target = 'lsusbdev', source = ['src/listdevs.c'], LIBS = [libusb_bin])
