import os
import json
import os.path
from math import ceil, log2, pow

# This is a code generation tool!

def gen_read(packet, file):
    file.write(f"""
void read(char* buf, size_t len){{
  {packet["structname"]} encoded;
  memcpy(&encoded,buf,len);
""")
    if "fields" in packet:
        for field in packet["fields"]:
            file.write(f"  //convert {field['name']}\n")
    file.write("}\n\n")

def gen_write(packet, file):
    file.write(f"""
void write(Writeable& dest){{
  {packet["structname"]} encoded;
""")

    if "fields" in packet:
        for field in packet["fields"]:
            file.write(f"  //convert {field['name']}\n")

    file.write("  dest.write((char *) &encoded, sizeof(encoded));\n}\n\n")


def verify_packet(packet):
    if "fields" in packet:
        # total bits in packet
        bitlength = sum([field["bits"] for field in packet["fields"]])
        # find the right uncompressed c primative type
        for field in packet["fields"]:
            if field["encoding"] == "float":
                field["ctype"] = "double"
            elif field["encoding"] == "int":
                int_bits = 8*(2**ceil(log2(field["bits"]/8)))
                field["ctype"] = "uint" + str(int_bits) + "_t"
            elif field["encoding"] == "bool":
                field["ctype"] = "bool"
    else:
        bitlength = 0
    # calculate bytes in packet
    packet["length"] = ceil(bitlength/8)


def gen_interface(field, file):
    file.write(f'''{field["ctype"]} get_{field["name"]}() {{ return {field["name"]}; }}\n''')
    file.write(f'''void set_{field["name"]}({field["ctype"]} new_val) {{ {field["name"]} = new_val; }}\n\n''')


def gen_struct(packet, file):
    structName = packet["name"].lower() + "_t"
    file.write(f"typedef struct __attribute__((__packed__)) {structName} {{\n")

    if "fields" in packet:
        for field in packet["fields"]:
            file.write(f"  unsigned {field['name'].lower()} : {str(field['bits'])};\n")

    file.write(f"}} {structName};\n")
    packet["structname"] = structName

def gen_class(packet, file):
    file.write(f'class {packet["name"]} : public Packet{{\n'
               f"protected:\n"
               f'const size_t length = sizeof({packet["structname"]});\n'
               f'const uint8_t id = {hex(packet["id"])};\n\n')

    if "fields" in packet:
        for field in packet["fields"]:
            file.write(f'{field["ctype"]} {field["name"]};\n')

    file.write("\npublic:\n")

    if "fields" in packet:
        for field in packet["fields"]:
            gen_interface(field, file)

    gen_read(packet, file)
    gen_write(packet, file)

    file.write("size_t packet_len() { return length; }\n"
               "};\n")


def gen_module(packet):
    verify_packet(packet)
    filepath = os.path.join("src/packet/", packet["name"] + ".h")
    os.makedirs(os.path.dirname(filepath), exist_ok=True)
    with open(filepath, "w") as srcfile:
        srcfile.write("""\
#pragma once
#include "Packet.h"
#include <stdint.h>
#include <cstring>
"""
        )

        # generate the packet struct
        gen_struct(packet, srcfile)
        srcfile.write("\n")
        gen_class(packet, srcfile)

        srcfile.write(f"""
static {packet["name"]} g_{packet["name"]};
""")


with open("utils/packet.json", "r") as specfile:
    spec = json.load(specfile)
    for packet in spec["packets"]:
        gen_module(packet)
