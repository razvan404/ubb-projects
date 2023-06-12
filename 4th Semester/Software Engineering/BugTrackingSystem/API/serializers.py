from rest_framework import serializers

from API.models import Employee, Bug


class EmployeeSerializer(serializers.ModelSerializer):
    class Meta:
        model = Employee
        fields = ('id', 'username', 'type')


class LoginEmployeeSerializer(serializers.ModelSerializer):
    username = serializers.CharField(validators=[])

    class Meta:
        model = Employee
        fields = ('username', 'password')


class CreateEmployeeSerializer(serializers.ModelSerializer):
    class Meta:
        model = Employee
        fields = ('username', 'password', 'type')


class UpdateEmployeeSerializer(serializers.ModelSerializer):
    username = serializers.CharField(validators=[])

    class Meta:
        model = Employee
        fields = ('username', 'password', 'type')


class BugSerializer(serializers.ModelSerializer):
    reporter = serializers.CharField(source='reporter.username', read_only=True)
    solver = serializers.SerializerMethodField(read_only=True)

    class Meta:
        model = Bug
        fields = ('id', 'title', 'description', 'status', 'created_at', 'reporter', 'solver')

    @staticmethod
    def get_solver(obj):
        return obj.solved_by.username if obj.status == 'fixed' \
            else obj.assigned_to.username if obj.assigned_to else None


class BugDetailsSerializer(serializers.ModelSerializer):
    class Meta:
        model = Bug
        fields = ('title', 'description')
