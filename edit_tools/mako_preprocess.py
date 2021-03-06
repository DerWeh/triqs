from mako.template import Template
import sys, os,re, glob, fnmatch, subprocess

# --- Parsing the arguments of the script and options
import argparse

parser = argparse.ArgumentParser(description="""
Preprocess the mako files.

For each xxx.mako.?pp file, it generates xxx.?pp file by:
 - remove the //mako, /*mako
 - replace the MAKO_Abc by ${Abc}
 - render with mako
 - call clang format

Options -c : just check that the current files are the preprocessed one 
""", 
formatter_class=argparse.RawTextHelpFormatter)

parser.add_argument('--input_dir', '-i',  help="", default = 'triqs')
parser.add_argument('--check', '-c',  action='store_true', help="Check only")

args = parser.parse_args()
indir = args.input_dir

def all_hcpp_files(dir) : 
    """Generate the name of all files *.mako.?pp in dir, recursively"""
    for root, dirnames, filenames in os.walk(dir):
        for filename in fnmatch.filter(filenames, '*.mako.?pp'):
            yield os.path.join(root, filename)

def process_one_file(fi): 
    # if not check mode, write the file, otherwise just compare
    if args.check : 
        print "Checking file : ", fi
    else:  
        print "Preprocessing file : ", fi
 
    code = open(fi, 'r').read()

    # remove the comment //mako 
    code = re.sub(r'//\s*mako\s*','', code)

    # remove the comments /*mako .... */
    code = re.sub(r'/\*\s*mako(.*?)\*/', r'\1', code, flags= re.DOTALL) 

    # replace MAKO_ABC by ${ABC} : NB no _
    code = re.sub(r'MAKO_([a-zA-Z0-9]+)', r'${\1}', code)
 
    # call mako engine
    code = Template(code).render()
   
    # Adding the warning on top of the file
    sep = '//' + 40*'*'
    code = '\n'.join([sep, '// GENERATED BY MAKO : DO NOT EDIT', sep, code])

    # clang formatting the code. clang format must be in the path !
    p = subprocess.Popen(['clang-format'], stdin = subprocess.PIPE, stdout=subprocess.PIPE, shell=True)
    code2 = p.communicate(code)[0]
    code = code2 if code2 else code

    # output file : same name, without mako
    fo = fi.replace(".mako",'').replace('.hpp','.hxx').replace('.cpp','.cxx')

    # if not check mode, write the file, otherwise just compare
    if args.check : 
        assert code == open(fo, 'r').read(), "File %s differ"%fo
    else:  
        open(fo, 'w').write(code)
 
# main
for fi in all_hcpp_files(indir): 
    process_one_file(fi)

if args.check : 
    print "Ok"
