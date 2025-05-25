import os
import shutil
import filecmp

def main():
    
    print('compiling gen.cpp')
    CMD = 'g++ gen.cpp -o cpp_files/gen.out'
    os.system(CMD)
    print('DONE!!!!')
    print('compiling wrong_code.cpp')
    CMD = 'g++ code.cpp -o cpp_files/wrong_code.out'
    os.system(CMD)
    print('DONE!!!!')

    print('compiling right_code.cpp')
    CMD = 'g++ code2.cpp -o cpp_files/right_code.out'
    os.system(CMD)
    print('DONE!!!!')
    if os.path.isdir('test_case'):
        shutil.rmtree('test_case')

    os.mkdir('test_case')

    lim = 10000
    for i in range(1,lim+1):
        

        CMD = './cpp_files/gen.out'
        os.system(CMD)
        shutil.copyfile('output.txt', 'test_case/test_case_{}'.format(i))

        shutil.copyfile('output.txt', 'input.txt')


        CMD = './cpp_files/wrong_code.out'
        os.system(CMD)
        shutil.copyfile('output.txt', 'tmp1.txt')

        CMD = './cpp_files/right_code.out'
        os.system(CMD)
        shutil.copyfile('output.txt', 'tmp2.txt')

        ok = True
        with open('tmp1.txt') as f1, open('tmp2.txt') as f2:
            for line1, line2 in zip(f1, f2):
                if line1 == line2:
                    continue
                else: 
                    ok = False

        if not ok:
            print("TEST CASE {}: FAILED".format(i))
            import pdb; pdb.set_trace()
        else:
            print("TEST CASE {}: PASSED".format(i))     

        os.remove('tmp1.txt')
        os.remove('tmp2.txt')        

if __name__ == '__main__':
    main()



