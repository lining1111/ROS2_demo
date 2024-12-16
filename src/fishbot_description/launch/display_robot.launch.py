import os
import launch
import launch_ros
from ament_index_python.packages import get_package_share_path


def generate_launch_description():
    # 获取默认urdf的路径
    urdf_package_path = get_package_share_path('fishbot_description')
    default_urdf_path = os.path.join(urdf_package_path, 'urdf/fishbot', 'fishbot.urdf.xacro')
    default_rviz_path = os.path.join(urdf_package_path, 'config', 'display_robot_model.rviz')
    # 声明一个urdf目录的参数，方便修改
    action_declare_arg_mode_path = launch.actions.DeclareLaunchArgument(
        name='model', default_value=str(default_urdf_path), description='加载的模型文件路径'
    )

    # 通过文件路径，获取内容
    substitutions_command_result = launch.substitutions.Command(
        ['xacro ', launch.substitutions.LaunchConfiguration('model')])

    # 将内容转换为参数值对象
    robot_description_value = launch_ros.descriptions.ParameterValue(substitutions_command_result, value_type=str)

    # 相当于 ros2 run robot_state_publisher robot_state_publisher --ros-args --ros-args --p robot_description:=URDF文件的内容
    action_robot_state_publisher = launch_ros.actions.Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description': robot_description_value}]
    )
    # 相当于 ros2 run joint_state_publisher joint_state_publisher --ros-args --ros-args --p robot_description:=URDF文件的内容
    action_joint_state_publisher = launch_ros.actions.Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        parameters=[{'robot_description': robot_description_value}]
    )

    action_rviz_node = launch_ros.actions.Node(
        package='rviz2',
        executable='rviz2',
        arguments=['-d ', default_rviz_path]
    )

    return launch.LaunchDescription([
        action_declare_arg_mode_path,
        action_robot_state_publisher,
        action_joint_state_publisher,
        action_rviz_node,
    ])
