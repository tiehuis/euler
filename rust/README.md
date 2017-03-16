### Running

Current solutions require the [Rust](https://www.rust-lang.org/) compiler and
the Cargo package manager. They can then be run with the following style:

```
cargo run --release --bin 100
```

Some solutions read from external data which is located in the `res` folder.
In order for the paths to work, the above command should always be run from
the folder which contains this README.
