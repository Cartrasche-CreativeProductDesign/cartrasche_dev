#!/usr/bin/env python3

import rospy
from std_msgs.msg import String
import paho.mqtt.client as mqtt

# MQTT settings
MQTT_BROKER = "broker.hivemq.com"  # Replace with your MQTT broker address
MQTT_PORT = 1883
MQTT_TOPIC = "your/mqtt/topic"  # Replace with your MQTT topic

def on_connect(client, userdata, flags, rc):
    rospy.loginfo("Connected to MQTT broker with result code " + str(rc))
    client.subscribe(MQTT_TOPIC)

def on_message(client, userdata, msg):
    rospy.loginfo("MQTT message received: " + msg.topic + " " + str(msg.payload))
    ros_publisher.publish(msg.payload.decode())

def mqtt_subscriber():
    rospy.init_node('mqtt_subscriber_node', anonymous=True)

    global ros_publisher
    ros_publisher = rospy.Publisher('mqtt_to_ros_topic', String, queue_size=10)
    
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(MQTT_BROKER, MQTT_PORT, 60)

    client.loop_start()

    rospy.loginfo("MQTT subscriber node started")
    rospy.spin()

    client.loop_stop()
    client.disconnect()

if __name__ == '__main__':
    try:
        mqtt_subscriber()
    except rospy.ROSInterruptException:
        pass
