from functools import cache


class File:
    def __init__(self, abs_path, size) -> None:
        self.size = size
        self.path = abs_path


class Folder:
    def __init__(self, abs_path):
        self.files = []
        self.path = abs_path
        self.subfolders = []

    @cache
    def get_size(self):
        return sum([fol.get_size() for fol in self.subfolders]) + sum([file.size for file in self.files])


def get_path(path):
    if len(path) == 1 or len(path) == 0:
        return "/"
    else:
        return "/" + "/".join(path)[1:]


fs = {"/": Folder("/")}
all_folders = [fs["/"]]
path = []
for l in open("input", "r").readlines():
    spl = l.split()
    if spl[0] == "$":
        if spl[1] == "cd":
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

print("Part 1:", sum([s for x in all_folders if (s := x.get_size()) < 100000]))
print("Part 2:", min([s for x in all_folders if (s := x.get_size()) >= 30000000 - (70000000 - fs["/"].get_size())]))
