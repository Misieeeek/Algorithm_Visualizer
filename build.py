import subprocess
import sys


def build(type):
    subprocess.run(
        ["conan", "install", ".", "--build=missing", "-s", f"build_type={type}"],
        check=True,
    )
    subprocess.run(["cmake", "--preset", f"conan-{type.lower()}"], check=True)
    subprocess.run(
        ["cmake", "--build", "--preset", f"conan-{type.lower()}", "--parallel"],
        check=True,
    )


print("1) Debug\n2) Release\n3) Both")
choice = input("Choose [1/2/3]: ")

if choice == "1":
    build("Debug")
elif choice == "2":
    build("Release")
elif choice == "3":
    build("Debug")
    build("Release")
else:
    print("Error")
    sys.exit(1)
