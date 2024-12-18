import subprocess
import sys
sys.path.append('lib/')

print()
print("Building...")

subprocess.run(['python', 'build.py', 'build', '--build-lib=./lib'])


# Testing
import pybind_test

print()
print("Testing...")
assert pybind_test.add(1,2) == 3, "Add function wasn't worked"
print("Add function was tested")

obj = pybind_test.MyTestClass("some_name")
assert obj.name() == 'some_name', "Constructor wasn't worked normally"
print("Constructor was tested")

obj.setName("new_name")
assert obj.name() == 'new_name', "Method wasn't worked normally"
print("Method was tested")

assert pybind_test.global_lib_var == 100, "Global var library failed"
print("Global var tested")
print()

print("Testing was completed!")