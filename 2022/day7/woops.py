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

    def __str__(self) -> str:
        return (
            "<Folder med "
            + str(len(self.subfolders))
            + " subfoldre og "
            + str(len(self.files))
            + " filer. Dennes size: "
            + str(self.get_size())
            + " >"
        )

    def __repr__(self) -> str:
        return self.__str__()

    def get_size(self):
        print("Skal finne size for " + self.path)
        tot = 0
        for folder in self.subfolders:
            subfolder_value = folder.get_size()
            print("adder", subfolder_value, "til tot fra subfolder", str(folder))
            tot += subfolder_value
        for file in self.files:
            print("adder ", file.size, "fra fil")
            tot += file.size
        return tot


def get_path(path):
    print("Skal finne abs_path for", path)
    if len(path) == 1 or len(path) == 0:
        return "/"
    # jelif len(path) == 2:
    # return "/" + path[1]
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

    print("Leste dette:", l)
    print("Current path er:", get_path(path))

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
            # print("Skal fikse fs for", path, ", som oversettes til", get_path(path))
            print("Skal legge", spl[1], "inn i fs under mappe", get_path(path), ". Path er:", path)
            # for p in get_path(lie)
            glob_path = get_path(path)
            # fol = fs.get(glob_path, Folder(glob_path))
            parent_folder = fs.get(glob_path)  # , Folder(glob_path))
            print("Har funnet parent folder:", parent_folder, "på path", glob_path)
            new_path = glob_path + "/" + spl[1]
            new_folder = Folder(new_path)
            parent_folder.subfolders.append(new_folder)
            print("Lagret denne folderen til path:", new_path)
            fs[new_path] = new_folder
            all_folders.append(new_folder)

        else:
            # ls
            print("Skal lager størrelsen av", spl[1], "til", path)
            print("Den str er", spl[0])
            parsedNumber = int(spl[0])
            abs_path = get_path(path)
            folder = fs[abs_path]
            file_path = abs_path + "/" + spl[1]
            folder.files.append(File(file_path, spl[0]))


print("Antall folders:", len(all_folders))
print(all_folders)

print("Fs:")
print(fs)
# print(fs["//a"].get_size())


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
print("Må fri", must_free)
curr_min = 99**99
cands = []
print(curr_min)
for folder in all_folders:
    size = folder.get_size()
    if size >= must_free:
        cands.append(size)

print("Part 2:", min(cands))
