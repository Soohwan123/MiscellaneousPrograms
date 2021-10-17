using HelpdeskViewModels;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading.Tasks;
using Xunit;

namespace CaseempdyTests
{
    public class EmployeeViewModelTests
    {
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
            model.Lastname = "Lauersen";
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
    }
}