1.vim�������-vundle

Vundle���ص㣺

    ��.vimrc�м�¼��������Ĳ��
    ��װ���ò�������� �ű�/����
    �������ò��
    �������������п���VIM�ű�
    ����δʹ�õĲ��
    �����һ�ж�����ֱ��ͨ���ı�����ģʽ������

Vundle���Զ�����

    �����㰲װ�ű�������·��
    ��װ�͸��º��������ɰ�����ǩ

��װVundle
git clone https://github.com/gmarik/Vundle.vim.git ~/.vim/bundle/Vundle.vim

���ò��

��.vimrc��������´��루������ӵĴ����ʽ����

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

��װ���

��VIM����������� :PluginInstall
����To install from command line: vim +PluginInstall +qall

��װ������ʾDone����ʾ��װ�ɹ���

ע��vundle���Լ��ֶ���װ����ķ�ʽ�����֣�vundle��װ�Ļ���~/.vim/bundle/�½������Ŀ¼�����Լ��ֶ���װ���һ��Ὣ*.vim��װ��~/.vim/pluginĿ¼�¡�

2.��.vimrc����Ӳ����
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

3.��.vimrc�жԲ����������
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
let NERDTreeShowHidden = 1 "NERDTREE��ʾ�����ļ�

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

4.��װ���

��VIM����������� :PluginInstall
����To install from command line: vim +PluginInstall +qall


5.������ֶ���װ���������ú���

a.ctags����ת��
����tags�ļ���
ctags -R --c++-kinds=+px --c-kinds=+px --fields=+iaS --extra=+f

ָ��tags�ļ�λ�ã�~/.vimrc�����ã�
set tags=tags;
set autochdir

ctrl+] ��ת��
ctrl+t ���� 
:tags //�г�����/��ת�Ĺ���

b.Taglist���г��ļ����к꣬ȫ�ֱ�����������
������ַ��http://www.vim.org/scripts/script.php?script_id=273

~/.vimrc�����ã�
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

c.WinManager(�ļ����������)
���ص�ַ��http://www.vim.org/scripts/script.php?script_id=95

~/.vimrc�����ã�
let g:winManagerWindowLayout='FileExplorer|TagList'
nmap <F3> :WMToggle<CR>
nmap <F12> :!ctags -R<CR> 
���һ��Ϊ ����ctags

d.NERDTree(����WinManager��������vimrc����ʱע�͵���)
������ַ��http://www.vim.org/scripts/script.php?script_id=1658

~/.vimrc���������
"let NERDTreeWinPos='left'
"noremap <F7> :NERDTreeToggle<CR>


e.cscope
sudo apt-get install cscope
cscope -Rbq //���������ļ�
:cs add path/cscope.out path //vim����������ļ�λ�ã�ע���ߵ�path

:cs find c function  �鿴function�����õ�λ��
:cs find s ���ұ�c����
:cs find g ���ұ�����
:cs find d ���ұ��������õĺ���
:cs find t ���ұ��ַ���
:cs find e ���ұ�egrepģʽ
:cs find f ���ұ��ļ�
:cs find i ���Ұ������ļ����ļ�

��~/.vimrc�����set cscopequickfix=s-,c-,d-,i-,t-,e-
����ͨ��:cs find xxx����ĳ�����ź󣬻�������ת����һ���ҵ��÷��ų��ֵ�λ�ã�
Ȼ�����ͨ��:copen����quickfix���ڣ���quickfix��������ʾ���г��ֵ�λ�á�

��~/.vimrc����ӿ�ݼ���Ctrl+Shift+-��
nmap <C-_>s :cs find s <C-R>=expand("<cword>")<CR><CR>
nmap <C-_>g :cs find g <C-R>=expand("<cword>")<CR><CR>
nmap <C-_>c :cs find c <C-R>=expand("<cword>")<CR><CR>
nmap <C-_>t :cs find t <C-R>=expand("<cword>")<CR><CR>
nmap <C-_>e :cs find e <C-R>=expand("<cword>")<CR><CR>
nmap <C-_>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
nmap <C-_>i :cs find i <C-R>=expand("<cfile>")<CR><CR>
nmap <C-_>d :cs find d <C-R>=expand("<cword>")<CR><CR>

f.QuickFix���г���ѯ�����
��~/.vimrc����ӿ�ݼ�
nmap <F5> :copen<cr>
nmap <F6> :cclose<cr>
nmap <F7> :cn<cr>
nmap <F8> :cp<cr>

g.��������Ͳ��� Buffer -- ���: MiniBufExplorer
���ص�ַ http://www.vim.org/scripts/script.php?script_id=159

��~/.vimrc�����
let g:miniBufExplMapWindowNavVim = 1
let g:miniBufExplMapWindowNavArrows = 1
let g:miniBufExplMapCTabSwitchBufs = 1
let g:miniBufExplModSelTarget = 1

h.c/h �ļ����໥�л� -- ���: A
���ص�ַ http://www.vim.org/scripts/script.php?script_id=31

:A ���� Buffer ���л��� c/h �ļ�
:AS ����ָ�ڲ��� c/h �ļ�
:AV ����ָ�ڲ��� c/h �ļ�
:AT �½�һ����ǩҳ���� c/h �ļ�

��~/.vimrc����ӿ�ݼ�
nnoremap <silent> <F4> :A<CR>



i.autoload_cscope.vim �Զ�����cscope.out
���ص�ַ http://www.vim.org/scripts/script.php?script_id=157

���úú�ʹ��ʱ��Ҫ���ǵļ������⣺
1.��ο��ٲ������Լ����뷨��Ҫ������ЩĿ¼���ļ����͵ȣ�����ctags��cscope��Ҫ��tags��cscope.out
2.����Զ�������Щ���ɵ��ļ�

������������������ô���ַ�����
����1:a.����alias
      b.��д�Զ��ű�
����2:a.ʹ��autoload_cscope.vim������
      b.����~/.vimrc

�������Լ���ʵ���������������aliasΪһ����Ŀʹ�ã���д�ű�Ϊandroid��Ŀ����(�����д�ű�ʱ��Ҫȷ��ʹ�õ��Ǿ���·����������ܻ�����⣬�����Vim���Զ�����cscope.out ��)���ű���������
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

ע��cscopeֻĬ������c�ļ����������ݿ⣬��Ĭ������c++��java���ļ�������Ĭ�ϻὫcscope.files����ļ��м�¼�������ļ������������ݿ⡣���⣬��androidԴ���Ŀ¼��ֱ��������Щ�ļ�����Ҫgit��������������һ��Ŀ¼��������Щ�ļ���




�Զ�����cscope.outʹ������vimrc����ʹ��autoload_cscope.vim������(��Ϊ����ֻ�д�c�ļ�����Ч)��
����~/.vimrc���£�
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
