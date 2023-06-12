from API.repositories import *


class ServiceException(Exception):
    def __init__(self, message: str):
        self.__message = message

    @property
    def message(self) -> str:
        return self.__message


class UnauthorizedException(ServiceException):
    def __init__(self, message: str = 'user unauthorized'):
        super().__init__(message)


class NotFoundException(ServiceException):
    def __init__(self, message: str = 'not found'):
        super().__init__(message)


class BadRequestException(ServiceException):
    def __init__(self, message: str = 'bad request'):
        super().__init__(message)


class SessionService:
    employee_session_repository = EmployeeSessionRepository()

    @staticmethod
    def create_session(employee: Employee, session: str) -> None:
        SessionService.employee_session_repository.save(EmployeeSession(employee=employee, session=session))

    @staticmethod
    def delete_session(session: str) -> None:
        SessionService.employee_session_repository.delete(SessionService.validate_session(session))

    @staticmethod
    def validate_session(session: str, employee_type: str = None) -> EmployeeSession:
        if requester := SessionService.employee_session_repository.find_by_session(session=session):
            if requester is None or (employee_type is not None and requester.employee.type != employee_type):
                raise UnauthorizedException()
            return requester
        raise NotFoundException('employee not found')

    @staticmethod
    def find_employee_by_session(session: str) -> Employee:
        if employee_session := SessionService.employee_session_repository.find_by_session(session):
            return employee_session.employee
        raise NotFoundException('employee not found')


class EmployeeService:
    employee_repository = EmployeeRepository()

    @staticmethod
    def find_employee(username: str = None, password: str = None, session: str = None) -> Employee:
        if username is not None and password is not None:
            if employee := EmployeeService.employee_repository.find_by_username_and_password(username, password):
                return employee
            raise NotFoundException()
        elif session is not None:
            return SessionService.find_employee_by_session(session)
        else:
            raise BadRequestException()

    @staticmethod
    def find_all_employees(session: str) -> list[Employee]:
        SessionService.validate_session(session=session, employee_type='administrator')
        return EmployeeService.employee_repository.find_all()

    @staticmethod
    def create_employee(session: str, employee_username: str, employee_password: str,
                        employee_type: str) -> Employee:
        SessionService.validate_session(session=session, employee_type='administrator')
        employee = Employee(username=employee_username, password=employee_password, type=employee_type)
        EmployeeService.employee_repository.save(employee)
        return employee

    @staticmethod
    def update_employee(session: str, employee_id: int, employee_username: str, employee_password: str,
                        employee_type: str):
        SessionService.validate_session(session=session, employee_type='administrator')
        employee = EmployeeService.employee_repository.find_by_id(employee_id)
        if employee is None:
            raise NotFoundException()
        employee.username = employee_username
        employee.password = employee_password
        employee.type = employee_type
        EmployeeService.employee_repository.update(employee)

    @staticmethod
    def delete_employee(session: str, employee_id: int):
        SessionService.validate_session(session=session, employee_type='administrator')
        employee = EmployeeService.employee_repository.find_by_id(employee_id)
        if employee is None:
            raise NotFoundException()
        EmployeeService.employee_repository.delete(employee)


class BugService:
    bug_repository = BugRepository()

    @staticmethod
    def find_all_bugs(session: str) -> list[Bug]:
        SessionService.validate_session(session=session)
        return BugService.bug_repository.find_all()

    @staticmethod
    def find_all_tester_bugs(session: str) -> list[Bug]:
        tester = SessionService.validate_session(session=session, employee_type='tester').employee
        return tester.reported_bugs.all()

    @staticmethod
    def find_all_programmer_bugs(session: str) -> list[Bug]:
        programmer = SessionService.validate_session(session=session, employee_type='programmer').employee
        return programmer.bugs_to_solve.all()

    @staticmethod
    def create_bug(session: str, title: str, description: str) -> Bug:
        tester = SessionService.validate_session(session=session, employee_type='tester').employee
        bug = Bug(title=title, description=description, reporter=tester)
        BugService.bug_repository.save(bug)
        return bug

    @staticmethod
    def update_bug(session: str, bug_id: int, title: str = None, description: str = None, status: str = None):
        if title is not None and description is not None and status is None:
            SessionService.validate_session(session=session, employee_type='tester')
            bug = BugService.bug_repository.find_by_id(bug_id)
            if bug is None:
                raise NotFoundException('bug not found')
            if bug.status != 'unassigned':
                raise BadRequestException('cannot update bug because it\'s not unassigned')
            bug.title = title
            bug.description = description
            BugService.bug_repository.update(bug)
        elif title is None and description is None and status is not None:
            programmer = SessionService.validate_session(session=session, employee_type='programmer').employee
            bug = BugService.bug_repository.find_by_id(bug_id)
            if bug is None:
                raise NotFoundException('bug not found')
            elif status not in ['unassigned', 'assigned', 'fixed']:
                raise BadRequestException('invalid status')
            elif status == 'unassigned':
                if bug.status != 'assigned' or bug.assigned_to != programmer:
                    raise BadRequestException('cannot mark bug as unassigned because it\'s not assigned by you')
                bug.status = 'unassigned'
                bug.assigned_to = None
            elif status == 'assigned':
                if bug.status != 'unassigned':
                    raise BadRequestException('cannot assign bug because it\'s not unassigned')
                bug.status = 'assigned'
                bug.assigned_to = programmer
            elif status == 'fixed':
                if bug.status != 'assigned' or bug.assigned_to != programmer:
                    raise BadRequestException('cannot mark bug as fixed because it\'s not assigned by you')
                bug.status = 'fixed'
                bug.assigned_to = None
                bug.solved_by = programmer
            BugService.bug_repository.update(bug)
        else:
            raise BadRequestException()

    @staticmethod
    def delete_bug(session: str, bug_id: int):
        SessionService.validate_session(session=session, employee_type='tester')
        bug = BugService.bug_repository.find_by_id(bug_id)
        if bug is None:
            raise NotFoundException()
        if bug.status != 'unassigned':
            raise BadRequestException('cannot delete bug because it\'s not unassigned')
        BugService.bug_repository.delete(bug)

