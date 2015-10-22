import os

env = Environment()

env.ParseConfig('pkg-config --cflags --libs protobuf')

env.Append(CXXFLAGS=['-std=c++11', '-Wall', '-g'])

env.Append(CPPPATH=['/usr/local/include'])


env.Append(LIBS=['pthread', 'boost_system', 'boost_regex', 'boost_thread', 'boost_filesystem', 'boost_program_options'])


env.Append(LIBPATH=['/usr/local/lib'])


#env.Program('p', ['main.cc', 'cd_server.cc', 'cd_user_md.cc', 'cd_user.cc', 'cd_session.cc', 'cd_handler.cc', 'gpb/test.pb.cc', 'handler/get_user_info.cc', 'handler/set_user_info.cc'])

env.Program('crazydog', ['main.cc', 'cd_server.cc', 'cd_user_md.cc', 'cd_user.cc', 'cd_session.cc', 'cd_handler.cc', 'gpb/test.pb.cc', 'handler/get_user_info.cc', 'handler/set_user_info.cc'])
