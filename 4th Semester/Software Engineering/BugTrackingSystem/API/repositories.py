from API.models import *


class Repository:
    def find_by_id(self, identifier) -> object | None:
        pass

    def find_all(self) -> list:
        pass

    def save(self, entity) -> None:
        pass

    def update(self, entity) -> None:
        pass

    def delete(self, entity) -> None:
        pass


class EmployeeRepository(Repository):
    def __init__(self):
        self.__objects = Employee.objects

    def find_by_id(self, employee_id: int) -> Employee | None:
        try:
            return self.__objects.get(id=employee_id)
        except Employee.DoesNotExist:
            return None

    def find_by_username_and_password(self, username: str, password: str) -> Employee | None:
        try:
            return self.__objects.get(username=username, password=password)
        except Employee.DoesNotExist:
            return None

    def find_all(self) -> list:
        return self.__objects.all()

    def save(self, employee: Employee) -> None:
        employee.save()

    def update(self, employee: Employee) -> None:
        employee.save(update_fields=['username', 'password', 'type'])

    def delete(self, employee: Employee) -> None:
        employee.delete()


class EmployeeSessionRepository(Repository):
    def __init__(self):
        self.__objects = EmployeeSession.objects

    def save(self, employee_session: EmployeeSession) -> None:
        employee_session.save()

    def find_by_session(self, session: str) -> EmployeeSession | None:
        try:
            return self.__objects.get(session=session)
        except EmployeeSession.DoesNotExist:
            return None

    def delete(self, employee_session: EmployeeSession) -> None:
        employee_session.delete()


class BugRepository(Repository):
    def __init__(self):
        self.__objects = Bug.objects

    def find_by_id(self, bug_id: int) -> Bug | None:
        try:
            return self.__objects.get(id=bug_id)
        except Bug.DoesNotExist:
            return None

    def find_all(self) -> list:
        return self.__objects.all()

    def save(self, bug: Bug) -> None:
        bug.save()

    def update(self, bug: Bug) -> None:
        bug.save(update_fields=['title', 'description', 'status', 'assigned_to', 'solved_by'])

    def delete(self, bug: Bug) -> None:
        bug.delete()
