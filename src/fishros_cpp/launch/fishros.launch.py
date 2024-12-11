import launch
import launch_ros


# ros2 launch xxx 的命令后，可以在最后面加 --debug来打印调试的内容
# 这个名字是写死的，返回类型也是死的，后面执行启动 ros2 launch xxx  lll.launch.py 就是这样要求的(xxx包名，lll文件名)
def generate_launch_description():
    # 这样声明参数后，就可以直接在ros2 launch xxx.launch.py 后加 launch_max_speed:=xxx 来改变参数了，(这里使用的是在xxx.launch.py下 执行当前文件的做法)
    action_declare_arg_max_spped = launch.actions.DeclareLaunchArgument('launch_max_speed', default_value='2.0')

    # 海龟控制节点 相当于 ros2 run fishros_cpp turtle_control --ros-args -p max_speed:=2.0
    action_node_turtle_control = launch_ros.actions.Node(
        package='fishros_cpp',  # 包名
        executable="turtle_control",  # 生成的执行文件名
        output='screen',  # 输入打印到哪里
        # 向节点内传入rosparam 相当于
        parameters=[{'max_speed': launch.substitutions.LaunchConfiguration(
            'launch_max_speed', default='2.0')}],
        # arguments 向执行程序传入参数

    )
    # 巡检节点，这里是用的随机巡逻点
    action_node_patrol_client = launch_ros.actions.Node(
        package='fishros_cpp',
        executable="patrol_client",
        output='log',
    )
    # 小海龟模拟器节点
    action_node_turtlesim_node = launch_ros.actions.Node(
        package='turtlesim',
        executable='turtlesim_node',
        output='both',
    )

    # 合成启动描述并返回
    launch_description = launch.LaunchDescription([
        action_declare_arg_max_spped,
        action_node_turtle_control,
        action_node_patrol_client,
        action_node_turtlesim_node
    ])
    return launch_description
