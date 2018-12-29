import os
import json
import os.path
from math import ceil, log2, pow
# This is a Code Genneration tool!


def gen_read(packet, file):
    file.write("void read(char* buf, size_t len){\n" +
               packet["structname"] + " encoded;\n"
               "memcpy(&encoded,buf,len);\n\n")

    if "feilds" in packet:
        for feild in packet["feilds"]:
            file.write("//convert " + feild["name"] + "\n")

    file.write("}\n\n")


def gen_write(packet, file):
    file.write("void write(Writeable& dest){\n" +
               packet["structname"] + " encoded;\n\n")

    if "feilds" in packet:
        for feild in packet["feilds"]:
            file.write("//convert " + feild["name"] + "\n")

    file.write("dest.write((char *) &encoded, sizeof(encoded));\n"
               "}\n\n")


def verifyPacket(packet):
    if "feilds" in packet:
        # total bits in packet
        bitlength = sum([feild["bits"] for feild in packet["feilds"]])
        # find the right uncompressed c primative type
        for feild in packet["feilds"]:
            if feild["encoding"] == "float":
                feild["ctype"] = "double"
            elif feild["encoding"] == "int":
                int_bits = 8*(2**ceil(log2(feild["bits"]/8)))
                feild["ctype"] = "uint" + str(int_bits) + "_t"
            elif feild["encoding"] == "bool":
                feild["ctype"] = "bool"
    else:
        bitlength = 0
    # calculate bytes in packet
    packet["length"] = ceil(bitlength/8)


def gen_interface(feild, file):
    file.write(feild["ctype"] + " get_" + feild["name"] +
               "(){return " + feild["name"] + ";}\n")
    file.write("void set_" + feild["name"] + "(" + feild["ctype"] +
               " new_val){"+feild["name"]+" = new_val;}\n\n")


def genStruct(packet, file):
    structName = packet["name"].lower() + "_t"
    file.write("typedef struct __attribute__((__packed__)) "+structName+" {\n")

    if "feilds" in packet:
        for feild in packet["feilds"]:
            file.write("unsigned " +
                       feild["name"].lower() + " : " + str(feild["bits"]) + ";\n")

    file.write("} " + structName + ";\n")
    packet["structname"] = structName


def genClass(packet, file):

    file.write("class " + packet["name"] + " : public Packet{\n"
               "protected:\n"
               "const size_t length = " + str(packet["length"]) + ";\n"
               "const uint8_t id = " + str(packet["id"]) + ";\n\n")

    if "feilds" in packet:
        for feild in packet["feilds"]:
            file.write(feild["ctype"] + " " + feild["name"]+";\n")

    file.write("\npublic:\n")

    if "feilds" in packet:
        for feild in packet["feilds"]:
            gen_interface(feild, file)

    gen_read(packet, file)
    gen_write(packet, file)

    file.write("size_t packet_len(){return length;}\n"
               "};\n")


def genPktCode(packet):
    verifyPacket(packet)
    filepath = "src/packet/" + packet["name"] + ".cpp"
    os.makedirs(os.path.dirname(filepath), exist_ok=True)
    with open(filepath, "w") as srcfile:

        srcfile.write("#include \"Packet.hpp\"\n"
                      "#include <stdint.h>\n"
                      "#include <cstring>\n\n")

        # generate the packet struct
        genStruct(packet, srcfile)
        srcfile.write("\n")
        genClass(packet, srcfile)


spec = dict()

with open("utils/packet.json", "r") as specfile:
    spec = json.load(specfile)

for packet in spec["packets"]:
    genPktCode(packet)
