#!/usr/bin/env python3

import jinja2
import json
from typing import Union
import unicodedata


def normalize(s: str):
    return unicodedata.normalize("NFKD", s).encode("ascii", "ignore").decode("utf-8")


def quote(s):
    return f'"{s}"'


class Messages:
    static_message_names = (
        "init_message",
        "init_in_progress",
        "shutdown_confirmation",
        "checking_motor_brakes_confirmation",
        "start_checking_motor_brakes_confirmation",
        "checking_motor_brakes_in_progress",
        "checking_all_brakes_confirmation",
        "start_checking_all_brakes_confirmation",
        "checking_all_brakes_in_progress",
        "checking_all_brakes_done",
        "checking_brakes_failed",
        "end_of_top_rail",
        "end_of_bottom_rail",
        "collision_with_object",
        "platform_door_open",
        "platform_overloaded_idle",
        "platform_overloaded_estop",
        "grippers_error",
        "platform_rotated",
        "battery_low",
        "battery_almost_empty",
        "temperature_high",
        "recover_top_eor",
        "temperature_critical",
        "load_on_platform",
        "Estop_robot_pressed",
        "start_init_auto_mode",
        "both_controllers_manual_mode",
        "connection_problem",
        "safe_stop",
        "encoder_movement_error",
        "heartbeat_error",
        "speed_id_estop",
        "unknown_error",
    )
    dynamic_message_names = (
        ("active_status", 12),
        ("inactive_status", 12),
        ("load", 9),
    )

    def __init__(self, name: str, data: dict[str, Union[str, list[str]]]):
        assert (
            len(data["language_name"]) <= 16
        ), f"{data['language_name']} is longer than 16 characters"
        self.name = name
        self.language_name = data["language_name"]
        self.static_messages = list[tuple[str, list[str]]]()
        self.dynamic_messages = dict[str, str]()

        for name in Messages.static_message_names:
            content = [normalize(raw_mess) for raw_mess in data[name]]
            for message in content:
                assert len(message) <= 16, f"{message} has more than 16 characters"
            self.static_messages.append((name, content))

        for name, max_len in Messages.dynamic_message_names:
            raw_data = data[name]
            assert isinstance(raw_data, str)
            content = normalize(raw_data)
            for message in content:
                assert len(message) <= max_len, f"{message} has more than 16 characters"
            self.dynamic_messages[name] = content


def generate_cpp(data, output_path):
    env = jinja2.Environment(
        loader=jinja2.FileSystemLoader("."),
        block_start_string="[%",
        block_end_string="%]",
        variable_start_string="[[",
        variable_end_string="]]",
        trim_blocks=True,
        lstrip_blocks=True,
    )
    env.filters["quote"] = quote
    template = env.get_template("message_content.cpp.jinja")
    localized_messages = [Messages(name, data[name]) for name in data]
    with open(output_path, "w+") as f:
        f.write(template.render(localized_messages=localized_messages))


with open("messages.json") as f:
    data = json.load(f)

generate_cpp(data, "message_content.cpp")
