#!/usr/bin/env python3

import asyncio
import socket


def checksum(bytes):
    result = bytearray([0])
    for byte in bytes:
        result[0] = (result[0] + byte) % 256
    return result
    

async def handle_client(client_reader, client_writer):
    while True:
        data = await client_reader.read(20)
        if not data:
            break
        answer = checksum(data)
        client_writer.write(answer)
        await client_writer.drain()
    client_writer.close()

if __name__ == "__main__":
    host = '127.0.0.1'
    port = 1234

    loop = asyncio.get_event_loop()
    loop.create_task(asyncio.start_server(handle_client, host, port))
    loop.run_forever()
