import time
import subprocess

LAB_PATH = r'D:\ppd\p1'
CPP_EXE_PATH = LAB_PATH + r'\concurs\x64\Release'

if __name__ == '__main__':
    configs_cpp = [
        [[CPP_EXE_PATH + '/server.exe', '4', '4', '1'], [CPP_EXE_PATH + '/client.exe']],
        [[CPP_EXE_PATH + '/server.exe', '4', '4', '2'], [CPP_EXE_PATH + '/client.exe']],
        [[CPP_EXE_PATH + '/server.exe', '4', '4', '4'], [CPP_EXE_PATH + '/client.exe']],
        [[CPP_EXE_PATH + '/server.exe', '2', '2', '1'], [CPP_EXE_PATH + '/client.exe']],
        [[CPP_EXE_PATH + '/server.exe', '2', '2', '2'], [CPP_EXE_PATH + '/client.exe']],
        [[CPP_EXE_PATH + '/server.exe', '2', '2', '4'], [CPP_EXE_PATH + '/client.exe']],
        [[CPP_EXE_PATH + '/server.exe', '4', '2', '1'], [CPP_EXE_PATH + '/client.exe']],
        [[CPP_EXE_PATH + '/server.exe', '4', '2', '2'], [CPP_EXE_PATH + '/client.exe']],
        [[CPP_EXE_PATH + '/server.exe', '4', '2', '4'], [CPP_EXE_PATH + '/client.exe']],
        [[CPP_EXE_PATH + '/server.exe', '4', '8', '1'], [CPP_EXE_PATH + '/client.exe']],
        [[CPP_EXE_PATH + '/server.exe', '4', '8', '2'], [CPP_EXE_PATH + '/client.exe']],
        [[CPP_EXE_PATH + '/server.exe', '4', '8', '4'], [CPP_EXE_PATH + '/client.exe']]
    ]

    for config in configs_cpp:
        total_time = 0
        num_runs = 10

        for _ in range(num_runs):
            server, client = config

            start_time = time.time()
            server_process = subprocess.Popen(server)
            client_process = subprocess.Popen(client)
            server_process.wait()
            client_process.wait()
            total_time += time.time() - start_time

        average_time = total_time / num_runs
        print(f'For configuration {server}, average time taken: {average_time:.5f} seconds')