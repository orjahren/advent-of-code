from collections import defaultdict
from functools import cache


class File:
    def __init__(self, abs_path, size) -> None:
        self.size = int(size)
        self.path = abs_path


class Folder:
    def __init__(self, abs_path):
        self.files = []
        self.path = abs_path
        self.subfolders = []

    @cache
    def get_size(self):
        tot = 0
        for folder in self.subfolders:
            tot += folder.get_size()
        for file in self.files:
            tot += file.size
        return tot


def get_path(path):
    if len(path) == 1 or len(path) == 0:
        return "/"
    else:
        return "/" + "/".join(path)[1:]


ll = []
with open("input", "r") as f:
    ll = [x.strip() for x in f.readlines()]


fs = {"/": Folder("/")}
all_folders = [fs["/"]]

path = []
for l in ll:
    spl = l.split()
    if spl[0] == "$":
        cmd = spl[1]
        if cmd == "cd":
            if spl[2] != "..":
                path.append(spl[2])
            else:
                path.pop()
    else:
        if spl[0] == "dir":
            glob_path = get_path(path)
            parent_folder = fs.get(glob_path)
            new_path = glob_path + "/" + spl[1]
            new_folder = Folder(new_path)
            parent_folder.subfolders.append(new_folder)
            fs[new_path] = new_folder
            all_folders.append(new_folder)
        else:
            abs_path = get_path(path)
            folder = fs[abs_path]
            file_path = abs_path + "/" + spl[1]
            folder.files.append(File(file_path, int(spl[0])))

roof = 100000
res = 0
for folder in all_folders:
    size = folder.get_size()
    if size < roof:
        res += size
print("Part 1:", res)

must_free = 30000000 - (70000000 - fs["/"].get_size())
print("Part 2:", min([s for x in all_folders if (s := x.get_size()) >= must_free]))
