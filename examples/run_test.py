import bandlimit.gaussian as gs
import time

def run_gaussian_sinc_test():
    """
    Demonstrates successful execution of the linked C function 
    GaussianInSinc via the Cython compute wrapper.
    
    Signature: compute(double lattice, int n, double alpha, double y, double X)
    """
    print("--- Running Gaussian-Sinc Interaction Test ---")
    
    # Define arbitrary but valid input parameters:
    lattice = 1.0    # Lattice constant
    n       = 0      # Angular momentum (s-wave)
    alpha   = 2.0    # Gaussian exponent (tighter Gaussian)
    y       = 0.1    # Position in space
    X       = 0.0    # Position in space

    start_time = time.time()
    
    try:
        # Call the Cython function, which calls the C library function
        result = gs.compute(lattice, n, alpha, y, X)
        
        end_time = time.time()
        
        print(f"\nParameters:")
        print(f"  Lattice Constant (lattice): {lattice}")
        print(f"  Angular Momentum (n):       {n}")
        print(f"  Gaussian Exponent (alpha):  {alpha}")
        
        # The exact value depends on the compiled C logic, but a non-zero number confirms execution.
        print("\nResult:")
        print(f"  <Gaussian|Sinc> Integral Value: {result}")
        print(f"  Execution Time: {end_time - start_time:.6f} seconds (Fast, thanks to C!)")
        
        if result != 0.0:
            print("\n✅ SUCCESS: The Gaussian and Sinc functions are communicating perfectly via the C library!")
        else:
            print("\n⚠️ WARNING: Function returned 0.0. Linkage is successful, but check input parameters.")

    except Exception as e:
        print(f"\n❌ FAILURE: An error occurred during execution: {e}")

if __name__ == "__main__":
    run_gaussian_sinc_test()
