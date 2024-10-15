class Process:

    def __init__(self):
        self.mnt = {}
        self.mdt = {}
        self.plt = {}
        self.op = []
        self.index = 1
        return

    def process(self):
        ip = open("/home/pict/Documents/31484/macro/utils/data/ip.txt")
        flag = 0
        for l in ip:
            l = l.strip()
            if (len(l) == 0):
                continue
            l = l.lower()

            l = l.split()

            if (l[0] != "macro" and flag == 0):
                self.op.append(" ".join(l))
                continue

            if (l[0] == "macro"):
                flag = 2
            elif l[0] == "mend":
                flag = 0
                self.mdt[self.index] = " ".join(l)
                self.index += 1
            elif flag == 2:
                flag = 1
                self.mnt[l[0]] = self.index
                name = l[0]
                l[0] = len(l) - 1
                self.plt[name] = l
            else:
                self.mdt[self.index] = " ".join(l)
                self.index += 1

        mdt = open("/home/pict/Documents/31484/macro/utils/output/mdt", "w")
        mnt = open("/home/pict/Documents/31484/macro/utils/output/mnt", "w")
        plt = open("/home/pict/Documents/31484/macro/utils/output/plt", "w")
        op = open("/home/pict/Documents/31484/macro/utils/output/op", "w")

        for key in self.mdt.keys():
            mdt.write(f"{key} {self.mdt[key]} \n")
        for key in self.mnt.keys():
            mnt.write(f"{key} {self.mnt[key]} \n")
        for key in self.plt.keys():
            plt.write(f"{key} {self.plt[key]} \n")
        for l in self.op:
            op.write(l + "\n")

    def pass2(self):
        op = open("/home/pict/Documents/31484/macro/utils/output/op")
        mdt = open("/home/pict/Documents/31484/macro/utils/output/mdt")
        mnt = open("/home/pict/Documents/31484/macro/utils/output/mnt")
        plt = open("/home/pict/Documents/31484/macro/utils/output/plt")

        pass2 = open("/home/pict/Documents/31484/macro/utils/output/pass2")


