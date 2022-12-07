from collections import defaultdict


class File:
    def __init__(self, abs_path, size) -> None:
        self.name = None
        self.size = int(size)
        self.parent = None
        self.path = abs_path


class Folder:
    def __init__(self, abs_path):
        self.files = []
        self.parent = None
        self.path = abs_path
        self.subfolders = []

    def get_size(self):
        tot = 0
        for folder in self.subfolders:
            subfolder_value = folder.get_size()
            tot += subfolder_value
        for file in self.files:
            tot += file.size
        return tot


def get_path(path):
    if len(path) == 1 or len(path) == 0:
        return "/"
    else:
        return "/" + "/".join(path)[1:]


files = []
ll = []
# with open("small", "r") as f:
with open("input", "r") as f:
    ll = [x.strip() for x in f.readlines()]

dd = defaultdict(lambda: 0)

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
        pass
    else:

        if spl[0] == "dir":
            glob_path = get_path(path)
            parent_folder = fs.get(glob_path)  # , Folder(glob_path))
            new_path = glob_path + "/" + spl[1]
            new_folder = Folder(new_path)
            parent_folder.subfolders.append(new_folder)
            fs[new_path] = new_folder
            all_folders.append(new_folder)

        else:
            parsedNumber = int(spl[0])
            abs_path = get_path(path)
            folder = fs[abs_path]
            file_path = abs_path + "/" + spl[1]
            folder.files.append(File(file_path, spl[0]))


roof = 100000
res = 0
for folder in all_folders:
    size = folder.get_size()
    if size < roof:
        res += size
print("Part 1:", res)


av = 70000000
trenger_unused = 30000000
tot_used = fs["/"].get_size()
must_free = trenger_unused - (av - tot_used)
curr_min = 99**99
cands = []
for folder in all_folders:
    size = folder.get_size()
    if size >= must_free:
        cands.append(size)

print("Part 2:", min(cands))
