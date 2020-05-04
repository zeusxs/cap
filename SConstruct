def color_red(string):
    return '\033[01;31m%s\033[0m' % string

def color_gre(string):
    return '\033[01;32m%s\033[0m' % string

def color_yel(string):
    return '\033[01;33m%s\033[0m' % string

def color_mag(string):
    return '\033[01;35m%s\033[0m' % string

def color_cya(string):
    return '\033[01;36m%s\033[0m' % string

def check_cheader(header, include_quotes='""'):
    if not conf.CheckCHeader(header, include_quotes):
        Exit(1)

def check_cxxheader(header, include_quotes='""'):
    if not conf.CheckCXXHeader(header, include_quotes):
        Exit(1)

def check_cxxlib(libname, header):
    if not conf.CheckLibWithHeader(libname, header, 'cpp'):
        print 'not found cxx library %s ' % (color_cya(libname))
        Exit(1)

env = Environment()
conf = Configure(env)

check_cxxheader('sys/socket.h')
check_cxxheader('arpa/inet.h')
check_cxxheader('fcntl.h')
check_cxxheader('unistd.h')

check_cxxlib('libpcap', 'pcap/pcap.h')
check_cxxlib('libtins', 'tins/tins.h')

env = conf.Finish()

Program('cap', Glob('src/*.cpp'), LIBS=['tins', 'pthread'], LIBPATH=['/usr/lib', '/usr/local/lib'], CPPPATH="src")
