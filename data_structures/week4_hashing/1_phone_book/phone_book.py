from typing import Iterable, List


class Query:
    def __init__(self, query: List[str]) -> None:
        self.type = query[0]
        self.number = int(query[1])

        if self.type == "add":
            self.name = query[2]


def read_queries() -> List[Query]:
    n = int(input())

    return [Query(input().split()) for _ in range(n)]


def process_inefficient(queries: Iterable[Query]) -> List[str]:  # noqa: C901
    contacts: List[Query] = []
    result = []

    for cur_query in queries:
        if cur_query.type == "add":
            for contact in contacts:
                if contact.number == cur_query.number:
                    contact.name = cur_query.name
                    break
            else:
                contacts.append(cur_query)

        elif cur_query.type == "del":
            for j in range(len(contacts)):
                if contacts[j].number == cur_query.number:
                    contacts.pop(j)
                    break

        else:
            response = "not found"
            for contact in contacts:
                if contact.number == cur_query.number:
                    response = contact.name
                    break
            result.append(response)

    return result


def process(queries: List[Query]) -> List[str]:  # noqa: C901
    contact_map = {}
    result = []

    for cur_query in queries:
        if cur_query.type == "add":
            contact_map[cur_query.number] = cur_query.name
        elif cur_query.type == "del":
            contact_map.pop(cur_query.number, None)
        else:
            result.append(contact_map.get(cur_query.number, "not found"))

    return result


def write_responses(result: List[str]) -> None:
    print("\n".join(result))


if __name__ == "__main__":
    write_responses(process(read_queries()))
