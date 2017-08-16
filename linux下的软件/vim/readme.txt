1.vim插件管理-vundle

Vundle的特点：

    在.vimrc中记录和配置你的插件
    安装配置插件（又名 脚本/包）
    更新配置插件
    按名称搜索所有可用VIM脚本
    清理未使用的插件
    上面的一切都可以直接通过文本交互模式来进行

Vundle能自动……

    管理你安装脚本的运行路径
    安装和更新后重新生成帮助标签

安装Vundle
git clone https://github.com/gmarik/Vundle.vim.git ~/.vim/bundle/Vundle.vim

配置插件

在.vimrc中添加如下代码（必须添加的代码格式）：

set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

" The following are examples of different formats supported.
" Keep Plugin commands between vundle#begin/end.
" plugin on GitHub repo
" Plugin 'tpope/vim-fugitive'
" plugin from http://vim-scripts.org/vim/scripts.html
" Plugin 'L9'
" Git plugin not hosted on GitHub
" Plugin 'git://git.wincent.com/command-t.git'
" git repos on your local machine (i.e. when working on your own plugin)
" Plugin 'file:///home/gmarik/path/to/plugin'
" The sparkup vim script is in a subdirectory of this repo called vim.
" Pass the path to set the runtimepath properly.
" Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}
" Install L9 and avoid a Naming conflict if you've already installed a
" different version somewhere else.
" Plugin 'ascenator/L9', {'name': 'newL9'}

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line

安装插件

打开VIM输入下面命令： :PluginInstall
或者To install from command line: vim +PluginInstall +qall

安装完后会显示Done，表示安装成功。

注：vundle和自己手动安装插件的方式是两种，vundle安装的会在~/.vim/bundle/下建立插件目录，而自己手动安装插件一般会将*.vim安装在~/.vim/plugin目录下。

2.在.vimrc中添加插件：
"Taglist
Plugin 'taglist.vim'

"NERdTree
Plugin 'scrooloose/nerdtree'

"cscope
Plugin 'cscope.vim'

"a
Plugin 'a.vim'

"minibuexplorer
Plugin 'minibufexplorerpp'

3.在.vimrc中对插件进行配置
"ctags
set tags=tags;
set autochdir

" Tlist
if &diff
        let Tlist_Auto_Open=0 "don't autopen when compare two files
else
        let Tlist_Auto_Open=0 "autopen Tlist when open a file
endif
"set taglist window in right, delete the following line if you don't like
let Tlist_Use_Right_Window=0
let Tlist_Auto_Update=1
let Tlist_File_Fold_Auto_Close=1
"auto close Tlist when exiting file.
let Tlist_Show_One_File=1
let Tlist_Exit_OnlyWindow = 1

"NERDTree
map tt :NERDTreeToggle<CR>
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endif
let NERDTreeShowHidden = 1 "NERDTREE显示隐藏文件

"cscope
if has("cscope")
        set csprg=/usr/bin/cscope
        set csto=0
        set cst
        set csverb
        set cspc=3
        "add any database in current dir
        if filereadable("cscope.out")
		cs add cscope.out
        "else search cscope.out elsewhere
        else
                let cscope_file=findfile("cscope.out", ".;")
                let cscope_pre=matchstr(cscope_file, ".*/")
                if !empty(cscope_file) && filereadable(cscope_file)
                        exe "cs add" cscope_file cscope_pre
                endif
        endif
endif

set cscopetag
set cscopeverbose
set cscopetagorder=1
set cscopequickfix=s-,c-,d-,i-,t-,e-
nnoremap <leader>fa :call cscope#findInteractive(expand('<cword>'))<CR>
nnoremap <leader>l :call ToggleLocationList()<CR>

" s: Find this C symbol
nnoremap  <leader>fs :call cscope#find('s', expand('<cword>'))<CR>
" g: Find this definition
nnoremap  <leader>fg :call cscope#find('g', expand('<cword>'))<CR>
" d: Find functions called by this function
nnoremap  <leader>fd :call cscope#find('d', expand('<cword>'))<CR>
" c: Find functions calling this function
nnoremap  <leader>fc :call cscope#find('c', expand('<cword>'))<CR>
" t: Find this text string
nnoremap  <leader>ft :call cscope#find('t', expand('<cword>'))<CR>
" e: Find this egrep pattern
nnoremap  <leader>fe :call cscope#find('e', expand('<cword>'))<CR>
" f: Find this file  
nnoremap  <leader>ff:call cscope#find('f', expand('<cword>'))<CR>
" i: Find files #including this file
nnoremap  <leader>fi :call cscope#find('i', expand('<cword>'))<CR>

"Quickfix
nmap <F5> :copen<cr>
nmap <F6> :cclose<cr>
nmap <F7> :cn<cr>
nmap <F8> :cp<cr>

"a
nnoremap <silent> <F4> :A<CR>

"MiniBufExplorer
let g:miniBufExplMapWindowNavVim = 1
let g:miniBufExplMapWindowNavArrows = 1
let g:miniBufExplMapCTabSwitchBufs = 1
let g:miniBufExplModSelTarget = 1

4.安装插件

打开VIM输入下面命令： :PluginInstall
或者To install from command line: vim +PluginInstall +qall


5.各插件手动安装方法及配置含义

a.ctags（跳转）
生成tags文件：
ctags -R --c++-kinds=+px --c-kinds=+px --fields=+iaS --extra=+f

指定tags文件位置，~/.vimrc中设置：
set tags=tags;
set autochdir

ctrl+] 跳转到
ctrl+t 返回 
:tags //列出查找/跳转的过程

b.Taglist（列出文件所有宏，全局变量，函数）
下载网址：http://www.vim.org/scripts/script.php?script_id=273

~/.vimrc中设置：
" Tlist
if &diff
let Tlist_Auto_Open=0 "don't autopen when compare two files
else
let Tlist_Auto_Open=0 "autopen Tlist when open a file
endif
"set taglist window in right, delete the following line if you don't like
let Tlist_Use_Right_Window=0
let Tlist_Auto_Update=1 
let Tlist_File_Fold_Auto_Close=1
"auto close Tlist when exiting file.
let Tlist_Show_One_File=1
let Tlist_Exit_OnlyWindow = 1 

c.WinManager(文件浏览器窗口)
下载地址：http://www.vim.org/scripts/script.php?script_id=95

~/.vimrc中设置：
let g:winManagerWindowLayout='FileExplorer|TagList'
nmap <F3> :WMToggle<CR>
nmap <F12> :!ctags -R<CR> 
最后一行为 更新ctags

d.NERDTree(类似WinManager，这里在vimrc中暂时注释掉了)
下载网址：http://www.vim.org/scripts/script.php?script_id=1658

~/.vimrc内容中添加
"let NERDTreeWinPos='left'
"noremap <F7> :NERDTreeToggle<CR>


e.cscope
sudo apt-get install cscope
cscope -Rbq //生成索引文件
:cs add path/cscope.out path //vim中添加索引文件位置，注意后边的path

:cs find c function  查看function被调用的位置
:cs find s 查找本c符号
:cs find g 查找本定义
:cs find d 查找本函数调用的函数
:cs find t 查找本字符串
:cs find e 查找本egrep模式
:cs find f 查找本文件
:cs find i 查找包含本文件的文件

在~/.vimrc中添加set cscopequickfix=s-,c-,d-,i-,t-,e-
这样通过:cs find xxx查找某个符号后，会立即跳转到第一个找到该符号出现的位置，
然后可以通过:copen来打开quickfix窗口，在quickfix窗口中显示所有出现的位置。

在~/.vimrc中添加快捷键（Ctrl+Shift+-）
nmap <C-_>s :cs find s <C-R>=expand("<cword>")<CR><CR>
nmap <C-_>g :cs find g <C-R>=expand("<cword>")<CR><CR>
nmap <C-_>c :cs find c <C-R>=expand("<cword>")<CR><CR>
nmap <C-_>t :cs find t <C-R>=expand("<cword>")<CR><CR>
nmap <C-_>e :cs find e <C-R>=expand("<cword>")<CR><CR>
nmap <C-_>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
nmap <C-_>i :cs find i <C-R>=expand("<cfile>")<CR><CR>
nmap <C-_>d :cs find d <C-R>=expand("<cword>")<CR><CR>

f.QuickFix（列出查询结果）
在~/.vimrc中添加快捷键
nmap <F5> :copen<cr>
nmap <F6> :cclose<cr>
nmap <F7> :cn<cr>
nmap <F8> :cp<cr>

g.快速浏览和操作 Buffer -- 插件: MiniBufExplorer
下载地址 http://www.vim.org/scripts/script.php?script_id=159

在~/.vimrc中添加
let g:miniBufExplMapWindowNavVim = 1
let g:miniBufExplMapWindowNavArrows = 1
let g:miniBufExplMapCTabSwitchBufs = 1
let g:miniBufExplModSelTarget = 1

h.c/h 文件间相互切换 -- 插件: A
下载地址 http://www.vim.org/scripts/script.php?script_id=31

:A 在新 Buffer 中切换到 c/h 文件
:AS 横向分割窗口并打开 c/h 文件
:AV 纵向分割窗口并打开 c/h 文件
:AT 新建一个标签页并打开 c/h 文件

在~/.vimrc中添加快捷键
nnoremap <silent> <F4> :A<CR>



i.autoload_cscope.vim 自动加载cscope.out
下载地址 http://www.vim.org/scripts/script.php?script_id=157

配置好后，使用时需要考虑的几个问题：
1.如何快速并按照自己的想法（要包含哪些目录及文件类型等）生成ctags及cscope需要的tags及cscope.out
2.如何自动加载这些生成的文件

上网搜索，大致有这么几种方法：
问题1:a.设置alias
      b.编写自动脚本
问题2:a.使用autoload_cscope.vim这个插件
      b.配置~/.vimrc

这里结合自己的实际情况，采用设置alias为一般项目使用，编写脚本为android项目定制(这里编写脚本时，要确保使用的是绝对路径，否则可能会出问题，详见《Vim中自动加载cscope.out 》)。脚本内容如下
#!/bin/sh
OUT_PATH=${PWD}
SRC_PATH=${PWD}/radxa_rock_android4-4

if [ -d ${OUT_PATH} ];
then
    echo "Use current directory \"${OUT_PATH}\""
else
    echo "mkdir \"${OUT_PATH}\""
    mkdir ${OUT_PATH}
fi

if [ -d ${SRC_PATH}/frameworks -a -d ${SRC_PATH}/packages -a -d ${SRC_PATH}/hardware -a -d ${SRC_PATH}/system ];
then
    echo "Found framework packages hardware and system directory!!"
    find -L ${SRC_PATH}/frameworks -name "*.h" -o -name "*.cpp" -o -name "*.cc" -o -name "*.c" -o -name "*.xml" -o -name "*.mk" -o -name "*.java"|grep -vi '\.git'        >${OUT_PATH}/cscope.files
    echo "framework scann finish!"
    find -L ${SRC_PATH}/packages -name "*.h" -o -name "*.cpp" -o -name "*.cc" -o -name "*.c" -o -name "*.xml" -o -name "*.mk" -o -name "*.java"|grep -vi '\.git'          >>${OUT_PATH}/cscope.files
    echo "packages scann finish!!"
    find -L ${SRC_PATH}/hardware -name "*.h" -o -name "*.cpp" -o -name "*.cc" -o -name "*.c" -o -name "*.xml" -o -name "*.mk" -o -name "*.java"|grep -vi '\.git'          >>${OUT_PATH}/cscope.files
    echo "hardware scann finish!!"
    find -L ${SRC_PATH}/system -name "*.h" -o -name "*.cpp" -o -name "*.cc" -o -name "*.c" -o -name "*.xml" -o -name "*.mk" -o -name "*.java"|grep -vi '\.git'            >>${OUT_PATH}/cscope.files
    echo "sytstem scann finish!!"
else
    echo "Please run this script under the root of your project!!!"
fi
echo "For create ctags and cscope databases.."
ctags -L ${OUT_PATH}/cscope.files -f ${OUT_PATH}/tags && cscope -bq 
echo "Done!!"

注：cscope只默认生成c文件的索引数据库，会默认跳过c++和java的文件，但是默认会将cscope.files这个文件中记录的所有文件生成索引数据库。另外，在android源码根目录下直接生成这些文件，需要git，所以这里在上一层目录中生成这些文件。




自动加载cscope.out使用配置vimrc而不使用autoload_cscope.vim这个插件(因为好像只有打开c文件才有效)，
配置~/.vimrc如下：
if has("cscope")
    set csprg=/usr/bin/cscope
    set csto=0
    set cst
    set csverb
    set cspc=3
    "add any database in current dir  
    if filereadable("cscope.out")
        cs add cscope.out
    "else search cscope.out elsewhere  
    else
        let cscope_file=findfile("cscope.out", ".;")
        let cscope_pre=matchstr(cscope_file, ".*/")
        if !empty(cscope_file) && filereadable(cscope_file)
            exe "cs add" cscope_file cscope_pre
        endif
    endif
endif
 
set cscopetag
set cscopeverbose
set cscopetagorder=1
set cscopequickfix=s-,c-,d-,i-,t-,e-
