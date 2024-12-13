import launch
import launch_ros


def generate_launch_description():

    # 静态发布tf
    action_node_tf_static = launch_ros.actions.Node(
        package='fishros_cpp',  # 包名
        executable="demo_tf_static_broadcaster",  # 生成的执行文件名
        #output='screen',  # 输入打印到哪里
    )
    # 动态发布tf
    action_node_tf_dynamic = launch_ros.actions.Node(
        package='fishros_cpp',
        executable="demo_tf_dynamic_broadcaster",
       # output='screen',
    )
    # 监听tf
    action_node_tf_listener = launch_ros.actions.Node(
        package='fishros_cpp',
        executable='demo_tf_listener',
        output='screen',
    )

    # 合成启动描述并返回
    launch_description = launch.LaunchDescription([
        action_node_tf_static,
        action_node_tf_dynamic,
        action_node_tf_listener
    ])
    return launch_description