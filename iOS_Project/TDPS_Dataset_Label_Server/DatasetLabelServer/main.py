from tcp_server_full_function import *

if __name__ == '__main__':
    while True:
        try:
            tcp_server_full_function()
        except KeyboardInterrupt:
            exit()
        except:
            continue
