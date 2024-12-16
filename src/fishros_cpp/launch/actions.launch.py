import launch
from ament_index_python import get_package_share_directory
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():
    # 声明是否启动rqt 可以直接使用 startup_rqt:=True/False
    action_declare_startup_rqt = launch.actions.DeclareLaunchArgument('startup_rqt', default_value='False')
    startup_rqt = launch.substitutions.LaunchConfiguration('startup_rqt', default_value='False')

    # 动作1启动其他launch 相当于执行了 ros2 launch turtlesim multisim.launch.py
    multisim_launch_path = [get_package_share_directory('turtlesim'), '/launch/', 'multisim.launch.py']
    action_include_launch = launch.actions.IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            multisim_launch_path
        )
    )

    # 动作2 打印数据
    action_log_info = launch.actions.LogInfo(msg=str(multisim_launch_path))

    # 动作3 执行进程 执行一个命令行 ros2 topic list
    action_topic_list = launch.actions.ExecuteProcess(
        condition=launch.conditions.IfCondition(startup_rqt),
        cmd=['rqt']
    )
    # 动作4 组织动作成组
    action_group = launch.actions.GroupAction([
        # 动作5 定时器
        launch.actions.TimerAction(
            period=2.0,
            actions=[action_include_launch],
        ),
        launch.actions.TimerAction(
            period=4.0,
            actions=[action_topic_list],
        ),
    ])

    # 合成启动描述并返回
    launch_description = launch.LaunchDescription([
        action_declare_startup_rqt,
        action_log_info,
        action_group,
    ])
    return launch_description
