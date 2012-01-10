// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-store=region -plugin-arg-analyzer -analyzer-constraints=range -fblocks -plugin-arg-analyzer -analyzer-opt-analyze-nested-blocks -plugin-arg-analyzer -analyzer-checker=core,experimental.deadcode.IdempotentOperations -plugin-arg-analyzer -analyzer-max-loop -plugin-arg-analyzer 3 -verify %s
// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-store=region -plugin-arg-analyzer -analyzer-constraints=range -fblocks -plugin-arg-analyzer -analyzer-opt-analyze-nested-blocks -plugin-arg-analyzer -analyzer-checker=core,experimental.deadcode.IdempotentOperations -plugin-arg-analyzer -analyzer-max-loop -plugin-arg-analyzer 4 -verify %s
// RUN: %clang_cc1 -plugin analyzer -plugin-arg-analyzer -analyzer-store=region -plugin-arg-analyzer -analyzer-constraints=range -fblocks -plugin-arg-analyzer -analyzer-opt-analyze-nested-blocks -plugin-arg-analyzer -analyzer-checker=core,experimental.deadcode.IdempotentOperations %s -verify

void always_warning() { int *p = 0; *p = 0xDEADBEEF; } // expected-warning{{Dereference of null pointer (loaded from variable 'p')}}

// This test case previously caused a bogus idempotent operation warning
// due to us not properly culling warnings due to incomplete analysis of loops.
int pr8403()
{
        int i;
        for(i=0; i<10; i++)
        {
                int j;
                for(j=0; j+1<i; j++)
                {
                }
        }
        return 0;
}

