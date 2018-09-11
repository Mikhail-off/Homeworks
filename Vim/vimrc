set number
set tabstop=4
set shiftwidth=4
set smarttab
set expandtab
set smartindent
set pastetoggle=<f2>
syntax enable
set nocompatible
filetype off

set rtp+=~/.vim/bundle/Vundle.vim

call vundle#begin()
Plugin 'VundleVim/Vundle.vim'
Plugin 'scrooloose/nerdtree'
Plugin 'Raimondi/delimitMate'
Plugin 'Valloric/YouCompleteMe'
Plugin 'octol/vim-cpp-enhanced-highlight'
Plugin 'bling/vim-airline'
Plugin 'vim-airline/vim-airline-themes'
Plugin 'calculuswhiz/vim-GAS-x86_64-highlighter'
call vundle#end()
filetype plugin indent on


set completeopt-=preview
let g:ycm_global_ycm_extra_conf = "~/.vim/.ycm_extra_conf.py"
let g:ycm_extra_conf_vim_data = [ '&filetype' ]

map <F3> :NERDTreeToggle<CR>

let g:airline#extensions#tabline#enabled = 1
let g:airline_enable_fugitive=1
let g:airline_enable_syntastic=1
let g:airline_enable_bufferline=1
set laststatus=2
set noshowmode

colorscheme vorange
let g:rehash256 = 1





