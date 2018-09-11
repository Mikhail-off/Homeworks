ftopts = {
  'cpp': [
    '-Wall',
    '-Wextra',
    '-x', 'c++',
    '-std=c++11',
  ],
  'c': [
    '-Wall',
    '-Wextra',
    '-Werror'
    '-gnu',
    '-x', 'c',
    '-I', '.',
  ],
  'objc': [
    '-x', 'objective-c',
    '-I', '.',
  ],
}

def FlagsForFile(filename, **kwargs):
  ft = 'cpp'
  client_data = None
  if kwargs and 'client_data' in kwargs:
    client_data = kwargs['client_data']
    if client_data and '&filetype' in client_data:
      ft = client_data['&filetype']

  try:
    opts = ftopts[ft]
  except:
    opts = ftopts['cpp']

  return {
    'flags': opts,
  }
