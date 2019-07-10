from building import *
Import('rtconfig')

src   = []
cwd   = GetCurrentDir()

# add nt5510 src files.
if GetDepend('PKG_USING_NT5510'):
    src += Glob('src/nt5510.c')

if GetDepend('PKG_USING_NT5510_SAMPLE'):
    src += Glob('samples/nt5510_sample.c')

# add nt5510 include path.
path  = [cwd + '/inc']

# add src and include to group.
group = DefineGroup('nt5510', src, depend = ['PKG_USING_NT5510'], CPPPATH = path)

Return('group')
