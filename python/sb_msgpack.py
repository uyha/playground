from io import BytesIO
from msgpack import Packer, Unpacker

packer: Packer = Packer()

buffer = BytesIO()
buffer.write(packer.pack(1))
buffer.write(packer.pack(2))
buffer.write(packer.pack(3))
buffer.write(packer.pack(4))

buffer.seek(0)

unpacker = Unpacker(buffer)
for item in unpacker:
    print(item)
