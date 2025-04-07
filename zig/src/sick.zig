const CpuOutput = packed struct(u8) {
    estop: bool,
    reference_point_set: bool,
};
