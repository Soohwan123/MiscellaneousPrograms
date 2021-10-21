using HelpdeskDAL;
using System;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace HelpdeskViewModels
{
    public class DepartmentViewModel
    {
        private DepartmentDAO _model;

        public int Id { get; set; }
        public string Name { get; set; }

        //constructor

        public DepartmentViewModel()
        {
            _model = new DepartmentDAO();
        }

        public async Task<List<DepartmentViewModel>> GetAll()
        {
            List<DepartmentViewModel> allVms = new List<DepartmentViewModel>();
            try
            {
                List<Department> allDepartments = await _model.GetAll();
                foreach (Department div in allDepartments)
                {
                    DepartmentViewModel vm = new DepartmentViewModel();
                    vm.Id = div.Id;
                    vm.Name = div.DepartmentName;
                    allVms.Add(vm);
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return allVms;
        }
    }


}
