import sys
import re
import subprocess
import os
import json


def GetPortAndIp(port, ip):
    scriptDir = os.path.dirname(os.path.realpath(__file__))
    
    if sys.platform == "win32":
        convertExe = os.path.join(scriptDir, "convert.exe")
    else:
        convertExe = os.path.join(scriptDir, "convert")

    try:
        output = subprocess.check_output([convertExe, str(port), str(ip)], text=True)
    except subprocess.CalledProcessError as e:
        print(f"Error executing {convertExe}: {e}")
        sys.exit(1)

    try:
        portIpDict = json.loads(output)
    except json.JSONDecodeError as e:
        print(f"Error parsing JSON from {convertExe} output: {e}")
        sys.exit(1)

    return portIpDict

def ReplacePortAndIp(filePath, port, ip):
    with open(filePath, 'r') as file:
        content = file.read()

    content = re.sub(r'PORTHERE', port, content)
    content = re.sub(r'IPHERE', ip, content)

    with open(filePath, 'w') as file:
        file.write(content)

def back(filePath):
    with open(filePath, 'r') as file:
        content = file.read()

    content = re.sub(r'^#define H_PORT.*$', '#define H_PORT PORTHERE', content, flags=re.MULTILINE)
    content = re.sub(r'^#define H_IP.*$', '#define H_IP IPHERE', content, flags=re.MULTILINE)

    with open(filePath, 'w') as file:
        file.write(content)

if __name__ == "__main__":
    HeaderPath = "include/main.h"
    if sys.argv[1] == "back":
        back(HeaderPath)
        sys.exit(0)
    else:
        try:
            port = int(sys.argv[1])
        except ValueError:
            print("Error: Port must be an number.")
            sys.exit(1)
        ip = sys.argv[2]

        Ipv4Pattern = r'^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$'

        if re.match(Ipv4Pattern, ip):
            portIpDict = GetPortAndIp(port, ip)
            port = hex(int(portIpDict.get('port')))
            ip = hex(int(portIpDict.get('ip')))
            ReplacePortAndIp(HeaderPath, port, ip)
            sys.exit(0)
        
        print("Error: Ip is not a valid ipv4.")
        sys.exit(1)
