simple Gen
{
    gates:
        input in;
        output out;
}

simple TokenBucket
{
    gates:
        input in;
        output out;
}


network token_bucket
{
    submodules:
        generator: Gen;
        tocken_bucket: TokenBucket;
    connections:
		generator.out --> { delay = 100ms; } --> tocken_bucket.in;
		generator.in <-- { delay=100ms; } <-- tocken_bucket.out;
}