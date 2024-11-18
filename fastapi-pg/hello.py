import asyncio

from fastapi import FastAPI


class RequestCancelledMiddleware:
    def __init__(self, app):
        self.app = app

    async def __call__(self, scope, receive, send):
        if scope["type"] != "http":
            await self.app(scope, receive, send)
            return

        # Let's make a shared queue for the request messages
        queue = asyncio.Queue()

        async def message_poller(sentinel, handler_task):
            nonlocal queue
            while True:
                message = await receive()
                if message["type"] == "http.disconnect":
                    handler_task.cancel()
                    return sentinel  # Break the loop

                # Puts the message in the queue
                await queue.put(message)

        sentinel = object()
        handler_task = asyncio.create_task(self.app(scope, queue.get, send))
        asyncio.create_task(message_poller(sentinel, handler_task))

        try:
            return await handler_task
        except asyncio.CancelledError:
            print("Cancelling request due to disconnect")


app = FastAPI()
app.add_middleware(RequestCancelledMiddleware)


@app.get("/sleep")
async def sleeping():
    import random

    # Generate random number
    num_random = random.randint(1, 10000)
    print("Before blocking this, instance: ", num_random)
    await asyncio.sleep(10)
    print("Block over, let's go!", num_random)
    return {"random": num_random}
