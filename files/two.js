/*
 * This code is pointless, don't try to learn from it.
 */

var jsonObject = {
    verbose: { notEmpty: true },
    short: false,
    steps: ["One", "Two", "Three", "Four"]
};

jsonObject.steps.forEach((step) => delete step);

delete jsonObject.steps;

if (jsonObject.verbose && !(jsonObject.steps)) {
    printSuccessful();
}