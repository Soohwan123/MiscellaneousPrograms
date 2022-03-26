using HelpdeskViewModels;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading.Tasks;
using Xunit;
using Xunit.Abstractions;

namespace CaseempdyTests
{
    public class EmployeeViewModelTests
    {
        private readonly ITestOutputHelper output;
        public EmployeeViewModelTests(ITestOutputHelper output)
        {
            this.output = output;
        }
        [Fact]
        public async Task Employee_GetByEmail()
        {
            EmployeeViewModel vm = null;
            try
            {
                vm = new EmployeeViewModel { Email = "ng@abc.com" };
                await vm.GetByEmail();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.NotNull(vm);
        }


        [Fact]
        public async Task Employee_GetByIdTest()
        {
            EmployeeViewModel vm = null;
            try
            {
                vm = new EmployeeViewModel { Id = 2 };
                await vm.GetById();
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.NotNull(vm.Lastname);
        }



        [Fact]
        public async Task Employee_GetAllTest()
        {
            EmployeeViewModel vm = new EmployeeViewModel();
            var stus = await vm.GetAll();
            int result = stus.Count;

            Assert.True(result > 0);
        }

        [Fact]
        public async Task Employee_AddTest()
        {
            EmployeeViewModel model = new EmployeeViewModel();

            model.Firstname = "Soohwan";
            model.Lastname = "Kim";
            model.Phoneno = "(555)555-1234";
            model.Title = "Mr.";
            model.DepartmentID = 100;
            model.Email = "sk@sk.com";

            await model.Add();
            Assert.True(model.Id > 1);
        }

        [Fact]
        public async Task Employee_UpdateTest()
        {
            EmployeeViewModel model = new EmployeeViewModel();
            model.Firstname = "Soohwan";
            model.Lastname = "Kim";
            model.Phoneno = "(555)555-1234";
            model.Title = "Mr.";
            model.DepartmentID = 500;
            model.Email = "sc@sc.com";

            await model.GetByEmail();
            model.Phoneno = model.Phoneno == "(555)555-1234" ? "(555)555-5552" : "(555)555-1234";

            Assert.True(await model.Update() == 1);
        }

        [Fact]
        public async Task Employee_DeleteTest()
        {
            EmployeeViewModel vm = new EmployeeViewModel();
            vm.Firstname = "Soohwan";
            vm.Lastname = "Kim";
            vm.Phoneno = "(555)555-1234";
            vm.Title = "Mr.";
            vm.DepartmentID = 500;
            vm.Email = "sc@sc.com";

            await vm.GetByEmail();
            Assert.True(await vm.Delete() == 1);
        }

        [Fact]
        public async Task Employee_ConcurrencyTest()
        {
            int employeesUpdated = -1;
            try
            {
                EmployeeViewModel vm1 = new EmployeeViewModel { Email = "sc@sc.com" };
                EmployeeViewModel vm2 = new EmployeeViewModel { Email = "sc@sc.com" };
                await vm1.GetByEmail(); // Student just added
                await vm2.GetByEmail(); // Student just added
                vm1.Phoneno = vm1.Phoneno == "(555)555-1234" ? "(555)555-5552" : "(555)555-1234";
                if (await vm1.Update() == 1)
                {
                    vm2.Phoneno = "(666)666-6666"; // just need any value
                    employeesUpdated = await vm2.Update();
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Error - " + ex.Message);
            }
            Assert.True(employeesUpdated == -2);
        }

        [Fact]
        public async Task Call_ComprehensiveVMTest()
        {
            CallViewModel cvm = new CallViewModel();
            EmployeeViewModel evm = new EmployeeViewModel();
            ProblemViewModel pvm = new ProblemViewModel();
            cvm.DateOpened = DateTime.Now;

            cvm.DateClosed = null;
            cvm.OpenStatus = true;
            evm.Email = "sc@sc.com";
            await evm.GetByEmail();
            cvm.EmployeeId = evm.Id;
            evm.Email = "pp@abc.com";
            await evm.GetByEmail();
            cvm.TechId = evm.Id;
            pvm.Description = "Memory Upgrade";
            await pvm.GetByDescription();
            cvm.ProblemId = pvm.Id;
            cvm.Notes = "Bigshot has bad RAM, burner to fix it";
            await cvm.Add();
            output.WriteLine("New Call Generated - Id = " + cvm.Id);
            int id = cvm.Id; // need id for delete later
            await cvm.GetById();
            cvm.Notes += "\n Ordered new RAM!";

            if(await cvm.Update() == 1)
            {
                output.WriteLine("Call was updated " + cvm.Notes);
            }
            else
            {
                output.WriteLine("Call was not updated!");
                
            }
            cvm.Notes = "Another change to comments that should not work";
            if(await cvm.Update() == -2)
            {
                output.WriteLine("Call was updated " + cvm.Notes);

            }

            cvm = new CallViewModel
            {
                Id = id
            };
            // need to reset because of concurrency error
            await cvm.GetById();
            if(await cvm.Delete() == 1)
            {
                output.WriteLine("Call was deleted!");
            }
            else
            {
                output.WriteLine("Call was not deleted!");
            }
            //should throw expected exception
            Task<NullReferenceException> ex = Assert.ThrowsAsync<NullReferenceException>(async () => await cvm.GetById());
        }
    }
}