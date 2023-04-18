from typing import List, Sequence


class Request:
    def __init__(self, arrival_time: int, process_time: int) -> None:
        self.arrival_time = arrival_time
        self.process_time = process_time


class Response:
    def __init__(self, dropped: bool, start_time: int) -> None:
        self.dropped = dropped
        self.start_time = start_time


class Buffer:
    def __init__(self, size: int) -> None:
        self.size = size
        self.finish_times_queue: List[int] = []

    def process(self, request: Request) -> Response:
        while len(self.finish_times_queue) != 0 and self.finish_times_queue[0] <= request.arrival_time:
            self.finish_times_queue.pop(0)

        if len(self.finish_times_queue) == self.size:
            return Response(True, -1)

        start_time = max(request.arrival_time, self.finish_times_queue[-1] if len(self.finish_times_queue) else 0)
        self.finish_times_queue.append(start_time + request.process_time)

        return Response(False, start_time)


def read_requests(*, count: int) -> Sequence[Request]:
    requests = []
    for _ in range(count):
        arrival_time, process_time = map(int, input().strip().split())
        requests.append(Request(arrival_time, process_time))

    return requests


def process(*, requests: Sequence[Request], buffer: Buffer) -> Sequence[Response]:
    return [buffer.process(request) for request in requests]


def print_(*, responses: Sequence[Response]) -> None:
    for response in responses:
        print(response.start_time if not response.dropped else -1)


if __name__ == "__main__":
    size, count = map(int, input().strip().split())

    requests = read_requests(count=count)
    buffer = Buffer(size)

    responses = process(requests=requests, buffer=buffer)

    print_(responses=responses)
