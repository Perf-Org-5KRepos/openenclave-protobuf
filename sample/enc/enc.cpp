// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include <stdio.h>

// Include the trusted helloworld header that is generated
// during the build. This file is generated by calling the
// sdk tool oeedger8r against the helloworld.edl file.
#include "helloworld_t.h"
#include "hello.pb.h"

int ecall_run(const char *input,
    uint64_t input_len,
    char **output,
    uint64_t *output_len)
{

    hello_world::HelloOutput enclave_output;
    hello_world::HelloInput enclave_input;
    std::string str("Hello");

    printf("In Enclave");
    if (!enclave_input.ParseFromArray(input, input_len)) {
        printf("Could not parse input from array\n");
        return 1;
    }
    str = str + " " + enclave_input.to_greet();

    enclave_output.set_greeting_message(str);
    *output = (char*)oe_host_malloc(enclave_output.ByteSize());
    if(*output == nullptr)
    {
        printf("Out of memory\n");
        return 1;
    }
    
    if (!enclave_output.SerializeToArray(*output, enclave_output.ByteSize()))
    {
        printf("Serialization of enclave output failed\n");
        return 1;
    }
    *output_len = enclave_output.ByteSize();

    return 0;
}
