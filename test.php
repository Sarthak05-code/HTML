<?php

interface PaymentGateway
{
    public function processPayment(float $amount): bool;
}

class BankAccount implements PaymentGateway
{
    private float $balance = 0.0;

    public function __construct(float $initBalance)
    {
        if ($initBalance > 0) {
            // Fixed comparison
            $this->balance = $initBalance;
        }
    }

    public function deposit(float $amount): void
    {
        if ($amount > 0) {
            $this->balance += $amount; // Fixed logic to accumulate balance
        }
    }

    public function getBalance(): float
    {
        return $this->balance;
    }

    #[Override]
    public function processPayment(float $amount): bool
    {
        if ($amount <= $this->balance) {
            $this->balance -= $amount;
            return true;
        }
        return false;
    }
}

// Fixed Inheritance Hierarchy: Both are types of Structures
abstract class Structure
{
    abstract public function build(): void;
}

class Tower extends Structure
{
    #[Override]
    public function build(): void
    {
        echo "The tower is being built.\n";
    }
}

class Bridge extends Structure
{
    #[Override]
    public function build(): void
    {
        echo "The bridge is being built.\n";
    }
}

$bridge = new Bridge();
$bridge->build();

interface Shape
{
    public function calculateArea(): float;
}

class Circle implements Shape
{
    public function __construct(private float $radius) {}

    #[Override]
    public function calculateArea(): float
    {
        return pi() * $this->radius ** 2;
    }
}

class Rectangle implements Shape
{
    public function __construct(
        private float $length,
        private float $breadth,
    ) {}

    #[Override]
    public function calculateArea(): float
    {
        return $this->length * $this->breadth; // Fixed formula
    }
}

function printArea(Shape $shape): void
{
    echo "Area: " . $shape->calculateArea() . "\n";
}

$circle = new Circle(12);
$rectangle = new Rectangle(10, 12);
printArea($circle); // Area: 452.3893...
printArea($rectangle); // Area: 120

abstract class HasNumber // Capitalized class name
{
    abstract public function caller(): void;
}

class Number extends HasNumber
{
    #[Override]
    public function caller(): void
    {
        echo "Calling from the abstract class.\n";
    }
}

$number = new Number();
$number->caller();

?>
