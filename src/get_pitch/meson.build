# Programas del proyecto

# Programa get_pitch
exe = 'get_pitch'
src = ['get_pitch.cpp',  'pitch_analyzer.cpp']

get_pitch = executable(
    exe,
    sources: src,
    include_directories: inc,
    link_args: ['-lm', '-lsndfile'],
    link_with: lib_pav,
    install: true,
)

# Programa pitch_evaluate
exe = 'pitch_evaluate'
src = 'pitch_evaluate.cpp'

pitch_evaluate = executable(
    exe,
    sources: src,
    include_directories: inc,
    link_with: lib_pav,
    install: true,
)

# Programa PSO_pitch_evaluate
exe = 'PSO_pitch_evaluate'
src = 'PSO_pitch_evaluate.cpp'

PSO_pitch_evaluate = executable(
    exe,
    sources: src,
    include_directories: inc,
    link_with: lib_pav,
    install: true,
)
