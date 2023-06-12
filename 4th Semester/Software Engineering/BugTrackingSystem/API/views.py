from rest_framework import status
from rest_framework.response import Response
from rest_framework.views import APIView

from API.models import EmployeeSession
from API.serializers import *
from API.service import SessionService, EmployeeService, UnauthorizedException, NotFoundException, BugService, \
    BadRequestException


class EmployeeCredentialsView(APIView):
    def post(self, request):
        # Login
        serializer = LoginEmployeeSerializer(data=request.data)
        if not serializer.is_valid():
            return Response({'error': 'invalid request'}, status=status.HTTP_400_BAD_REQUEST)

        username = serializer.data.get('username')
        password = serializer.data.get('password')
        try:
            employee = EmployeeService.find_employee(username=username, password=password)
            if not self.request.session.exists(self.request.session.session_key):
                self.request.session.create()
            SessionService.create_session(employee=employee, session=self.request.session.session_key)
            return Response({}, status=status.HTTP_200_OK)
        except NotFoundException as ex:
            return Response({'error': ex.message}, status=status.HTTP_404_NOT_FOUND)

    def get(self, request):
        # Find by session
        if not self.request.session.exists(self.request.session.session_key):
            self.request.session.create()
        try:
            employee = EmployeeService.find_employee(session=self.request.session.session_key)
            serialized = EmployeeSerializer(employee)
            return Response(serialized.data, status=status.HTTP_200_OK)
        except NotFoundException as ex:
            return Response({'error': ex.message}, status=status.HTTP_404_NOT_FOUND)

    def delete(self, request):
        # Logout
        if not self.request.session.exists(self.request.session.session_key):
            self.request.session.create()
        try:
            SessionService.delete_session(session=self.request.session.session_key)
            return Response({}, status=status.HTTP_200_OK)
        except NotFoundException as ex:
            return Response({'error': ex.message}, status=status.HTTP_404_NOT_FOUND)


class AdminEmployeesView(APIView):
    def get(self, request):
        if not self.request.session.exists(self.request.session.session_key):
            self.request.session.create()
        try:
            employees = EmployeeService.find_all_employees(session=self.request.session.session_key)
            serialized = EmployeeSerializer(employees, many=True)
            return Response(serialized.data, status=status.HTTP_200_OK)
        except UnauthorizedException as ex:
            return Response({'error': ex.message}, status=status.HTTP_401_UNAUTHORIZED)

        # Create Employee

    def post(self, request):
        if not self.request.session.exists(self.request.session.session_key):
            self.request.session.create()
        serializer = CreateEmployeeSerializer(data=request.data)
        if not serializer.is_valid():
            return Response({'error': 'invalid request'}, status=status.HTTP_400_BAD_REQUEST)
        username = serializer.data.get('username')
        password = serializer.data.get('password')
        employee_type = serializer.data.get('type')
        try:
            EmployeeService.create_employee(session=self.request.session.session_key, employee_username=username,
                                            employee_password=password, employee_type=employee_type)
            return Response({'msg': 'account created successfully'}, status=status.HTTP_201_CREATED)
        except UnauthorizedException as ex:
            return Response({'error': ex.message}, status=status.HTTP_401_UNAUTHORIZED)

    # Update Employee
    def put(self, request, employee_id: int):
        if not self.request.session.exists(self.request.session.session_key):
            self.request.session.create()
        serializer = UpdateEmployeeSerializer(data=request.data)
        if not serializer.is_valid():
            return Response({'error': 'invalid request'}, status=status.HTTP_400_BAD_REQUEST)
        username = serializer.data.get('username')
        password = serializer.data.get('password')
        employee_type = serializer.data.get('type')
        try:
            EmployeeService.update_employee(session=self.request.session.session_key, employee_id=employee_id,
                                            employee_username=username, employee_password=password,
                                            employee_type=employee_type)
            return Response({'msg': 'account updated successfully'}, status=status.HTTP_200_OK)
        except UnauthorizedException as ex:
            return Response({'error': ex.message}, status=status.HTTP_401_UNAUTHORIZED)
        except NotFoundException as ex:
            return Response({'error': ex.message}, status=status.HTTP_404_NOT_FOUND)

    def delete(self, request, employee_id: int):
        if not self.request.session.exists(self.request.session.session_key):
            self.request.session.create()
        if not employee_id:
            return Response({'error': 'invalid request'}, status=status.HTTP_400_BAD_REQUEST)
        try:
            EmployeeService.delete_employee(session=self.request.session.session_key, employee_id=employee_id)
            return Response({'msg': 'account deleted successfully'}, status=status.HTTP_200_OK)
        except UnauthorizedException as ex:
            return Response({'error': ex.message}, status=status.HTTP_401_UNAUTHORIZED)
        except NotFoundException as ex:
            return Response({'error': ex.message}, status=status.HTTP_404_NOT_FOUND)


class BugsView(APIView):
    def get(self, request):
        if not self.request.session.exists(self.request.session.session_key):
            self.request.session.create()
        try:
            bugs = BugService.find_all_bugs(session=self.request.session.session_key)
            serialized = BugSerializer(bugs, many=True)
            return Response(serialized.data, status=status.HTTP_200_OK)
        except UnauthorizedException as ex:
            return Response({'error': ex.message}, status=status.HTTP_401_UNAUTHORIZED)


class TesterBugsView(APIView):
    def get(self, request):
        if not self.request.session.exists(self.request.session.session_key):
            self.request.session.create()
        try:
            bugs = BugService.find_all_tester_bugs(session=self.request.session.session_key)
            serialized = BugSerializer(bugs, many=True)
            return Response(serialized.data, status=status.HTTP_200_OK)
        except UnauthorizedException as ex:
            return Response({'error': ex.message}, status=status.HTTP_401_UNAUTHORIZED)

    # add bug
    def post(self, request):
        if not self.request.session.exists(self.request.session.session_key):
            self.request.session.create()
        serializer = BugDetailsSerializer(data=request.data)
        if not serializer.is_valid():
            return Response({'error': 'invalid request'}, status=status.HTTP_400_BAD_REQUEST)
        title = serializer.data.get('title')
        description = serializer.data.get('description')
        try:
            BugService.create_bug(session=self.request.session.session_key, title=title, description=description)
            return Response({'msg': 'bug reported successfully'}, status=status.HTTP_201_CREATED)
        except UnauthorizedException as ex:
            return Response({'error': ex.message}, status=status.HTTP_401_UNAUTHORIZED)

    # update bug
    def patch(self, request, bug_id: int):
        if not self.request.session.exists(self.request.session.session_key):
            self.request.session.create()
        serializer = BugDetailsSerializer(data=request.data)
        if not serializer.is_valid():
            return Response({'error': 'invalid request'}, status=status.HTTP_400_BAD_REQUEST)
        title = serializer.data.get('title')
        description = serializer.data.get('description')
        try:
            BugService.update_bug(session=self.request.session.session_key, bug_id=bug_id, title=title,
                                  description=description)
            return Response({'msg': 'bug updated successfully'}, status=status.HTTP_200_OK)
        except NotFoundException as ex:
            return Response({'error': ex.message}, status=status.HTTP_404_NOT_FOUND)
        except BadRequestException as ex:
            return Response({'error': ex.message}, status=status.HTTP_400_BAD_REQUEST)

    # delete bug
    def delete(self, request, bug_id: int):
        if not self.request.session.exists(self.request.session.session_key):
            self.request.session.create()
        try:
            BugService.delete_bug(session=self.request.session.session_key, bug_id=bug_id)
            return Response({'msg': 'bug deleted successfully'}, status=status.HTTP_200_OK)
        except NotFoundException as ex:
            return Response({'error': ex.message}, status=status.HTTP_404_NOT_FOUND)
        except BadRequestException as ex:
            return Response({'error': ex.message}, status=status.HTTP_400_BAD_REQUEST)


class ProgrammerBugsView(APIView):
    def get(self, request):
        if not self.request.session.exists(self.request.session.session_key):
            self.request.session.create()
        try:
            bugs = BugService.find_all_programmer_bugs(session=self.request.session.session_key)
            serialized = BugSerializer(bugs, many=True)
            return Response(serialized.data, status=status.HTTP_200_OK)
        except UnauthorizedException as ex:
            return Response({'error': ex.message}, status=status.HTTP_401_UNAUTHORIZED)

    # mark a bug as assigned / unassigned / fixed
    def patch(self, request, bug_id: int):
        if not self.request.session.exists(self.request.session.session_key):
            self.request.session.create()
        status_ = request.data.get('status')
        try:
            BugService.update_bug(session=self.request.session.session_key, bug_id=bug_id, status=status_)
            return Response({'msg': 'bug status updated successfully'}, status=status.HTTP_200_OK)
        except NotFoundException as ex:
            return Response({'error': ex.message}, status=status.HTTP_404_NOT_FOUND)
        except BadRequestException as ex:
            return Response({'error': ex.message}, status=status.HTTP_400_BAD_REQUEST)
