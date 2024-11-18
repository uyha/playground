from werkzeug.security import generate_password_hash, check_password_hash

# print(generate_password_hash("559865", method="pbkdf2"))
print(
    check_password_hash(
        "sha256$qbvIkC6NSuzLdqiP$a3fbd58d248dfeb2574db78bba4fa6aa5da51af40aef5fb0f7487fd2650c0452",
        "559865",
    )
)
